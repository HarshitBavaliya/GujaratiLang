package org.gujaratilang

/**
 * GujaratiLang v2.3.0 Native Android JNI Bridge
 * Provides high-performance in-process evaluation of GujaratiLang scripts on Android.
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
}
