package org.gujaratilang

/**
 * GujaratiLang v2.5.0 LTS Native Android JNI Bridge
 * Provides high-performance in-process evaluation of GujaratiLang scripts on Android,
 * reactive UI dispatching, and enterprise mobile capabilities (Biometrics, FCM, WorkManager, Keystore).
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
     */
    external fun cameraCapture(options: String = ""): String

    /**
     * GujaratiLang v2.4.0 Android Hardware: Opens the system photo gallery picker.
     */
    external fun pickImage(): String

    /**
     * GujaratiLang v2.4.0 Android Hardware: Reads device motion or environmental sensors.
     */
    external fun sensorRead(sensorType: String): String

    /**
     * GujaratiLang v2.4.0 Android Hardware: Controls native voice audio recording.
     */
    external fun audioRecord(action: String, path: String = ""): String

    /**
     * GujaratiLang v2.4.0 Android Hardware: Resolves the local sandboxed SQLite database file path.
     */
    external fun getDatabasePath(dbName: String = "app"): String

    /**
     * GujaratiLang v2.5.0 LTS Enterprise Mobile: Prompts native Biometric verification.
     */
    external fun biometricAuth(prompt: String = "Confirm Biometrics"): String

    /**
     * GujaratiLang v2.5.0 LTS Enterprise Mobile: Dispatches remote FCM push notification.
     */
    external fun pushNotify(title: String, body: String): String

    /**
     * GujaratiLang v2.5.0 LTS Enterprise Mobile: Schedules recurring background task with WorkManager.
     */
    external fun workSchedule(task: String, intervalMinutes: Double = 15.0): String

    /**
     * GujaratiLang v2.5.0 LTS Enterprise Mobile: Stores secret securely in Android Hardware Keystore.
     */
    external fun keystoreSecure(key: String, secret: String): String

    /**
     * GujaratiLang v2.5.0 LTS Enterprise Mobile: Reads secret securely from Android Hardware Keystore.
     */
    external fun keystoreRead(key: String): String
}
