package org.gujaratilang

import androidx.compose.foundation.layout.*
import androidx.compose.material3.*
import androidx.compose.runtime.*
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp

/**
 * GujaratiComposeRenderer: Native Jetpack Compose renderer for GujaratiLang v2.4.0.
 * Traverses declarative UI dictionary trees (ui_column, ui_row, ui_text, ui_button, ui_card, ui_input, ui_webview)
 * and dispatches touch events back to the GujaratiLang engine across JNI.
 */
object GujaratiComposeRenderer {

    @Composable
    fun RenderNode(node: Map<String, Any>, onEvent: (action: String, eventType: String) -> Unit) {
        val type = node["type"] as? String ?: return

        when (type) {
            "ui_column" -> {
                val children = node["children"] as? List<Map<String, Any>> ?: emptyList()
                Column(modifier = Modifier.fillMaxWidth().padding(8.dp)) {
                    for (child in children) {
                        RenderNode(child, onEvent)
                    }
                }
            }
            "ui_row" -> {
                val children = node["children"] as? List<Map<String, Any>> ?: emptyList()
                Row(modifier = Modifier.fillMaxWidth().padding(4.dp), horizontalArrangement = Arrangement.SpaceBetween) {
                    for (child in children) {
                        RenderNode(child, onEvent)
                    }
                }
            }
            "ui_text" -> {
                val content = node["content"] as? String ?: ""
                val style = node["style"] as? String ?: "normal"
                val textStyle = when (style) {
                    "headline" -> MaterialTheme.typography.headlineMedium
                    "caption" -> MaterialTheme.typography.bodySmall
                    else -> MaterialTheme.typography.bodyLarge
                }
                Text(text = content, style = textStyle, modifier = Modifier.padding(vertical = 4.dp))
            }
            "ui_button" -> {
                val label = node["label"] as? String ?: "Button"
                val action = node["action"] as? String ?: ""
                Button(
                    onClick = { onEvent(action, "click") },
                    modifier = Modifier.padding(vertical = 4.dp)
                ) {
                    Text(text = label)
                }
            }
            "ui_card" -> {
                val child = node["child"] as? Map<String, Any>
                Card(
                    modifier = Modifier.fillMaxWidth().padding(vertical = 6.dp),
                    elevation = CardDefaults.cardElevation(defaultElevation = 4.dp)
                ) {
                    Box(modifier = Modifier.padding(12.dp)) {
                        if (child != null) {
                            RenderNode(child, onEvent)
                        }
                    }
                }
            }
            "ui_input" -> {
                val placeholder = node["placeholder"] as? String ?: "Enter text..."
                var textValue by remember { mutableStateOf("") }
                OutlinedTextField(
                    value = textValue,
                    onValueChange = {
                        textValue = it
                        val action = node["action"] as? String ?: "on_input_change"
                        onEvent(action, it)
                    },
                    label = { Text(placeholder) },
                    modifier = Modifier.fillMaxWidth().padding(vertical = 4.dp)
                )
            }
            "ui_webview" -> {
                val url = node["url"] as? String ?: "https://gujaratilang.hp-square.com"
                val title = node["title"] as? String ?: "Web View"
                Card(
                    modifier = Modifier.fillMaxWidth().height(250.dp).padding(vertical = 6.dp),
                    elevation = CardDefaults.cardElevation(defaultElevation = 2.dp)
                ) {
                    Column(modifier = Modifier.padding(8.dp)) {
                        Text(text = title, style = MaterialTheme.typography.labelSmall)
                        Spacer(modifier = Modifier.height(4.dp))
                        Text(text = "🌐 Browsing: $url", style = MaterialTheme.typography.bodySmall)
                    }
                }
            }
        }
    }
}
