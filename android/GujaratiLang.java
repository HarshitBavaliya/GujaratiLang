package org.gujaratilang;

/**
 * GujaratiLang v2.2.0 Native Android Java JNI Interop Wrapper
 */
public final class GujaratiLang {
    static {
        try {
            System.loadLibrary("gujarati");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("GujaratiLang: libgujarati.so native library not found.");
        }
    }

    private GujaratiLang() {}

    public static native String evaluateScript(String script);
    public static native String executeFile(String filePath);
    public static native String getVersion();
}
