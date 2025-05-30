#define CAMERA_MODEL_AI_THINKER

#include "esp_camera.h"
#include "Arduino.h"

#define PWDN_GPIO_NUM     -1
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

void setup() {
    Serial.begin(115200);
    Serial.setTimeout(100);

    // Camera configuration
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;
    config.frame_size = FRAMESIZE_VGA;
    config.jpeg_quality = 10;  // Adjust quality (lower = better)
    config.fb_count = 1;

    delay(1000);
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("Camera Init Failed! Error code: 0x%x\n", err);
        return;
    }

    Serial.println("Camera Ready!");
}

void loop() {
    if (Serial.available()) {
        String command = Serial.readStringUntil('\n');
        command.trim();

        if (command == "START_STREAM") {
            Serial.println("Starting Live Stream...");
            streamLivePreview();
        } 
        else if (command == "CAPTURE_IMAGE") {
            Serial.println("Capturing Image...");
            captureAndSendImage();
        }
    }
}

// Function to capture and send image over Serial
void captureAndSendImage() {
    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) {
        Serial.println("Camera Capture Failed");
        return;
    }

    // Send image size first
    Serial.write((uint8_t*)&fb->len, sizeof(fb->len));

    // Send the image data
    Serial.write(fb->buf, fb->len);

    esp_camera_fb_return(fb);
    Serial.println("Image Sent!");
}

// Function to stream images over Serial
void streamLivePreview() {
    unsigned long startTime = millis();
    while (millis() - startTime < 5000) { // Stream for 5 seconds, then exit
        if (Serial.available()) {
            String stopCommand = Serial.readStringUntil('\n');
            if (stopCommand == "STOP_STREAM") {
                Serial.println("Stopping Stream...");
                return;
            }
        }

        camera_fb_t *fb = esp_camera_fb_get();
        if (!fb) {
            Serial.println("Frame capture failed");
            continue;
        }

        Serial.write((uint8_t*)&fb->len, sizeof(fb->len));
        Serial.write(fb->buf, fb->len);

        esp_camera_fb_return(fb);
        delay(100); // Adjust for frame rate
    }
    Serial.println("Stream Timeout, Exiting...");
}
