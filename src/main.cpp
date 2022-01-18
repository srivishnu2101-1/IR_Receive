#include <Arduino.h>

#include <IRremote.hpp>

#define IR_RECEIVE_PIN 15     // D15
#define IR_LED_FEEDBACK_PIN 2 // D2

void setup()
{
    Serial.begin(115200);
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

    /*
     * Start the receiver, enable feedback LED and take LED feedback pin from the internal boards definition
     */
    IrReceiver.begin(IR_RECEIVE_PIN, false, IR_LED_FEEDBACK_PIN);

    Serial.print(F("Ready to receive IR signals of protocols: "));
    printActiveIRProtocols(&Serial);
    Serial.print(F("at pin "));
    Serial.println(IR_RECEIVE_PIN);
}

void loop()
{
    /*
     * Check if received data is available and if yes, try to decode it.
     * Decoded result is in the IrReceiver.decodedIRData structure.
     *
     * E.g. command is in IrReceiver.decodedIRData.command
     * address is in command is in IrReceiver.decodedIRData.address
     * and up to 32 bit raw data in IrReceiver.decodedIRData.decodedRawData
     */
    if (IrReceiver.decode())
    {

        // Print a short summary of received data
        // IrReceiver.printIRResultShort(&Serial);
        if (IrReceiver.decodedIRData.protocol == NEC)
        {
            switch (IrReceiver.decodedIRData.decodedRawData)
            {
            case 0xBA45FF00 /* constant-expression */:
                Serial.println("BUTTON_CH_PLUS");
                break;
            case 0xB946FF00 /* constant-expression */:
                Serial.println("BUTTON_CH");
                break;
            case 0xB847FF00 /* constant-expression */:
                Serial.println("BUTTON_CH_MINUS");
                break;
            case 0xBB44FF00 /* constant-expression */:
                Serial.println("BUTTON_PREV");
                break;
            case 0xBF40FF00 /* constant-expression */:
                Serial.println("BUTTON_NEXT");
                break;
            case 0xBC43FF00 /* constant-expression */:
                Serial.println("BUTTON_PLAY");
                break;
            case 0xF807FF00 /* constant-expression */:
                Serial.println("BUTTON_VOL_MINUS");
                break;
            case 0xEA15FF00 /* constant-expression */:
                Serial.println("BUTTON_VOL_PLUS");
                break;
            default:
                Serial.printf("BUTTON_UNKNOWN %x\n", IrReceiver.decodedIRData.decodedRawData);
                break;
            }
        }

        /*
         * !!!Important!!! Enable receiving of the next value,
         * since receiving has stopped after the end of the current received data packet.
         */
        IrReceiver.resume(); // Enable receiving of the next value
    }
}