package org.gujaratilang;

import android.content.Context;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TextView;
import java.util.List;
import java.util.Map;

/**
 * GujaratiViewRenderer: Classic Android View / ViewGroup layout renderer for GujaratiLang v2.4.0.
 */
public class GujaratiViewRenderer {

    public interface UiEventListener {
        void onEvent(String action, String eventType, String data);
    }

    public static View render(Context context, Map<String, Object> node, UiEventListener listener) {
        if (node == null) return null;
        String type = (String) node.get("type");
        if (type == null) return null;

        switch (type) {
            case "ui_column": {
                LinearLayout col = new LinearLayout(context);
                col.setOrientation(LinearLayout.VERTICAL);
                List<Map<String, Object>> children = (List<Map<String, Object>>) node.get("children");
                if (children != null) {
                    for (Map<String, Object> child : children) {
                        View childView = render(context, child, listener);
                        if (childView != null) col.addView(childView);
                    }
                }
                return col;
            }
            case "ui_row": {
                LinearLayout row = new LinearLayout(context);
                row.setOrientation(LinearLayout.HORIZONTAL);
                List<Map<String, Object>> children = (List<Map<String, Object>>) node.get("children");
                if (children != null) {
                    for (Map<String, Object> child : children) {
                        View childView = render(context, child, listener);
                        if (childView != null) row.addView(childView);
                    }
                }
                return row;
            }
            case "ui_text": {
                TextView tv = new TextView(context);
                String content = (String) node.get("content");
                tv.setText(content != null ? content : "");
                return tv;
            }
            case "ui_button": {
                Button btn = new Button(context);
                String label = (String) node.get("label");
                final String action = (String) node.get("action");
                btn.setText(label != null ? label : "Button");
                btn.setOnClickListener(v -> {
                    if (listener != null && action != null) {
                        listener.onEvent(action, "click", "");
                    }
                });
                return btn;
            }
            case "ui_input": {
                EditText et = new EditText(context);
                String placeholder = (String) node.get("placeholder");
                et.setHint(placeholder != null ? placeholder : "");
                return et;
            }
            case "ui_webview": {
                TextView webLabel = new TextView(context);
                String url = (String) node.get("url");
                webLabel.setText("🌐 WebView: " + (url != null ? url : "about:blank"));
                return webLabel;
            }
            default:
                return null;
        }
    }
}
