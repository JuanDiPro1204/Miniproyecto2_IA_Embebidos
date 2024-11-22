#include <PDM.h>
#include <Miniproyecto_2_-_ElBueno_inferencing.h>  // Librería generada por Edge Impulse

/** Audio buffers, pointers and selectors */
typedef struct {
    int16_t *buffer;
    uint8_t buf_ready;
    uint32_t buf_count;
    uint32_t n_samples;
} inference_t;

static inference_t inference;
static signed short sampleBuffer[2048];
static bool debug_nn = false;

void setup() {
    Serial.begin(115200);    // Comunicación por USB (para depuración)
    Serial1.begin(9600);     // Comunicación en pines TX (D1) y RX (D0)

    while (!Serial);
    Serial.println("Configuración completa. Listo para la inferencia.");

    // Imprimir configuración del modelo
    ei_printf("Inferencing settings:\n");
    ei_printf("\tInterval: %.2f ms.\n", (float)EI_CLASSIFIER_INTERVAL_MS);
    ei_printf("\tFrame size: %d\n", EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE);
    ei_printf("\tSample length: %d ms.\n", EI_CLASSIFIER_RAW_SAMPLE_COUNT / 16);
    ei_printf("\tNo. of classes: %d\n", EI_CLASSIFIER_LABEL_COUNT);

    if (microphone_inference_start(EI_CLASSIFIER_RAW_SAMPLE_COUNT) == false) {
        ei_printf("Error: No se pudo iniciar la inferencia con el micrófono.\n");
        return;
    }
}

void loop() {
    ei_printf("Inferencia iniciando en 2 segundos...\n");
    delay(2000);

    ei_printf("Grabando...\n");

    if (!microphone_inference_record()) {
        ei_printf("Error: Fallo en la grabación de audio.\n");
        return;
    }

    ei_printf("Grabación completa.\n");

    signal_t signal;
    signal.total_length = EI_CLASSIFIER_RAW_SAMPLE_COUNT;
    signal.get_data = &microphone_audio_signal_get_data;
    ei_impulse_result_t result = { 0 };

    EI_IMPULSE_ERROR r = run_classifier(&signal, &result, debug_nn);
    if (r != EI_IMPULSE_OK) {
        ei_printf("Error: Fallo en la ejecución del clasificador (%d).\n", r);
        return;
    }

    // Encontrar la clase con mayor probabilidad
    float max_value = 0.0;
    int max_index = 0;

    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
        if (result.classification[ix].value > max_value) {
            max_value = result.classification[ix].value;
            max_index = ix;
        }
    }

    const char* top_class = result.classification[max_index].label;
    ei_printf("Clase con mayor probabilidad: %s (%.5f)\n", top_class, max_value);

    // Enviar SOLO la clase con mayor probabilidad por Serial1 (pines RX/TX)
    Serial1.println(top_class);  // Enviar solo el nombre de la clase

    delay(1000);  // Esperar antes de la próxima inferencia
}

// Callback de datos listos para PDM (micrófono)
static void pdm_data_ready_inference_callback(void) {
    int bytesAvailable = PDM.available();
    int bytesRead = PDM.read((char *)&sampleBuffer[0], bytesAvailable);

    if (inference.buf_ready == 0) {
        for (int i = 0; i < bytesRead >> 1; i++) {
            inference.buffer[inference.buf_count++] = sampleBuffer[i];
            if (inference.buf_count >= inference.n_samples) {
                inference.buf_count = 0;
                inference.buf_ready = 1;
                break;
            }
        }
    }
}

// Iniciar el micrófono y configurar PDM
static bool microphone_inference_start(uint32_t n_samples) {
    inference.buffer = (int16_t *)malloc(n_samples * sizeof(int16_t));
    if (inference.buffer == NULL) {
        return false;
    }

    inference.buf_count = 0;
    inference.n_samples = n_samples;
    inference.buf_ready = 0;

    PDM.onReceive(&pdm_data_ready_inference_callback);
    PDM.setBufferSize(4096);

    if (!PDM.begin(1, EI_CLASSIFIER_FREQUENCY)) {
        ei_printf("Error: No se pudo iniciar PDM.\n");
        microphone_inference_end();
        return false;
    }

    PDM.setGain(127);
    return true;
}

// Terminar grabación del micrófono
static void microphone_inference_end(void) {
    PDM.end();
    free(inference.buffer);
}

// Esperar a que los datos estén listos
static bool microphone_inference_record(void) {
    inference.buf_ready = 0;
    inference.buf_count = 0;

    while (inference.buf_ready == 0) {
        delay(10);
    }
    return true;
}

// Obtener señal de audio en bruto
static int microphone_audio_signal_get_data(size_t offset, size_t length, float *out_ptr) {
    numpy::int16_to_float(&inference.buffer[offset], out_ptr, length);
    return 0;
}
