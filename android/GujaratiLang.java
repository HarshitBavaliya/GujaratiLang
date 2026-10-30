package org.gujaratilang;

/**
 * GujaratiLang v2.5.0 LTS Native Android JNI Bridge
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
    public static native String cameraCapture(String options);
    public static native String pickImage();
    public static native String sensorRead(String sensorType);
    public static native String audioRecord(String action, String path);
    public static native String getDatabasePath(String dbName);
    public static native String biometricAuth(String prompt);
    public static native String pushNotify(String title, String body);
    public static native String workSchedule(String task, double intervalMinutes);
    public static native String keystoreSecure(String key, String secret);
    public static native String keystoreRead(String key);
}
