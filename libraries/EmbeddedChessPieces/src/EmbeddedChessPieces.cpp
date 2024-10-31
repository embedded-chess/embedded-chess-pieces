#include "EmbeddedChessPieces.h"

double ECPColorDetection::isWhiteField() {
    double ambient = dezibot.chessColorDetection.getNormalizedAmbientValue();
    double red = dezibot.chessColorDetection.getNormalizedColorValue(RGBW_RED, ambient);
    double green = dezibot.chessColorDetection.getNormalizedColorValue(RGBW_GREEN, ambient);
    double blue = dezibot.chessColorDetection.getNormalizedColorValue(RGBW_BLUE, ambient);
    double white = dezibot.chessColorDetection.getNormalizedColorValue(RGBW_WHITE, ambient);

    double brightness = dezibot.chessColorDetection.calculateBrightness(red, green, blue);

    return brightness >= IS_WHITE_FIELD_THRESHOLD;
};

void ECPColorDetection::turnOnColorCorrectionLight() {
  uint32_t colorCorrectionWhite = dezibot.multiColorLight.color(
    COLOR_CORRECTION_LIGHT_R, COLOR_CORRECTION_LIGHT_G, COLOR_CORRECTION_LIGHT_B);
  dezibot.multiColorLight.setLed(BOTTOM, colorCorrectionWhite);
};

void ECPColorDetection::turnOffColorCorrectionLight() {
  dezibot.multiColorLight.setLed(BOTTOM, 0);
}
