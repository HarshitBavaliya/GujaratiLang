package org.gujaratilang

/**
 * GujaratiLang v2.4.0 Native Android JNI Bridge
 * Provides high-performance in-process evaluation of GujaratiLang scripts on Android,
 * reactive UI dispatching, and hardware sensor/media integrations.
 */
object GujaratiLang {
    init {
        try {
            System.loadLibrary("gujarati")
        } catch (e: UnsatisfiedLinkError) {
            System.err.println("GujaratiLang: libgujarati.so native library not found in apk lib path.")
        }
    }

    /**
     * Evaluates a dynamic GujaratiLang source code string in-memory.
     * @param script The source code in Gujarati, Standard English, or Romanized Gujarati.
     * @return Execution output or result string.
     */
    external fun evaluateScript(script: String): String

    /**
     * Executes a standalone .gj script file from local storage or asset cache.
     * @param filePath Absolute path to the .gj file.
     * @return Execution output string.
     */
    external fun executeFile(filePath: String): String

    /**
     * Returns the GujaratiLang runtime engine version.
     */
    external fun getVersion(): String

    /**
     * Dispatches a user touch or input event into the active GujaratiLang runtime.
     * @param componentId Target widget or callback action name.
     * @param eventType Event type ("click", "change", "submit").
     * @param eventData Optional event payload.
     * @return Event handling result string.
     */
    external fun dispatchEvent(componentId: String, eventType: String, eventData: String = ""): String

    /**
     * GujaratiLang v2.4.0 Android Hardware: Captures a photo using the system Camera.
     * @param options Camera configuration options (JSON or comma-separated).
     * @return File URI of the captured image.
     */
    external fun cameraCapture(options: String = ""): String

    /**
     * GujaratiLang v2.4.0 Android Hardware: Opens the system photo gallery picker.
     * @return File URI of the selected image.
     */
    external fun pickImage(): String

    /**
     * GujaratiLang v2.4.0 Android Hardware: Reads device motion or environmental sensors.
     * @param sensorType "accelerometer", "gyroscope", "step_counter", or "light".
     * @return JSON string of sensor vector and magnitude.
     */
    external fun sensorRead(sensorType: String): String

    /**
     * GujaratiLang v2.4.0 Android Hardware: Controls native voice audio recording.
     * @param action "start" or "stop".
     * @param path Target audio file path.
     * @return Output audio path or status string.
     */
    external fun audioRecord(action: String, path: String = ""): String

    /**
     * GujaratiLang v2.4.0 Android Hardware: Resolves the local sandboxed SQLite database file path.
     * @param dbName Name of database.
     * @return Absolute path on the Android filesystem.
     */
    external fun getDatabasePath(dbName: String = "app"): String
}
