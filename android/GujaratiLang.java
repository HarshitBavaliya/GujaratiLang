package org.gujaratilang;

/**
 * GujaratiLang v2.3.0 Native Android JNI Bridge
 */
public class GujaratiLang {
    static {
        try {
            System.loadLibrary("gujarati");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("GujaratiLang: libgujarati.so native library not found.");
        }
    }

    public static native String evaluateScript(String script);
    public static native String executeFile(String filePath);
    public static native String getVersion();
    public static native String dispatchEvent(String componentId, String eventType, String eventData);
}
