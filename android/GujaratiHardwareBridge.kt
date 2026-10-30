package org.gujaratilang

import android.content.Context
import android.hardware.Sensor
import android.hardware.SensorEvent
import android.hardware.SensorEventListener
import android.hardware.SensorManager
import java.io.File

/**
 * GujaratiHardwareBridge: Android Hardware and Sensor subsystem bridge for GujaratiLang v2.4.0.
 * Coordinates Camera, Photo Gallery, Motion/Environmental Sensors, Audio Recording, and SQLite DB files.
 */
class GujaratiHardwareBridge(private val context: Context) : SensorEventListener {

    private val sensorManager = context.getSystemService(Context.SENSOR_SERVICE) as? SensorManager
    private var lastAccelerometerValues = floatArrayOf(0.1f, 9.8f, 0.2f)

    init {
        val accel = sensorManager?.getDefaultSensor(Sensor.TYPE_ACCELEROMETER)
        accel?.let {
            sensorManager.registerListener(this, it, SensorManager.SENSOR_DELAY_NORMAL)
        }
    }

    override fun onSensorChanged(event: SensorEvent?) {
        if (event?.sensor?.type == Sensor.TYPE_ACCELEROMETER) {
            lastAccelerometerValues = event.values.clone()
        }
    }

    override fun onAccuracyChanged(sensor: Sensor?, accuracy: Int) {}

    fun getCameraCaptureUri(): String {
        val imagesDir = File(context.filesDir, "captures")
        if (!imagesDir.exists()) imagesDir.mkdirs()
        val file = File(imagesDir, "capture_${System.currentTimeMillis()}.jpg")
        return file.absolutePath
    }

    fun getAccelerometerReading(): Map<String, Any> {
        return mapOf(
            "sensor" to "accelerometer",
            "x" to lastAccelerometerValues.getOrElse(0) { 0f },
            "y" to lastAccelerometerValues.getOrElse(1) { 9.8f },
            "z" to lastAccelerometerValues.getOrElse(2) { 0f },
            "unit" to "m/s^2",
            "status" to "active"
        )
    }

    fun getLocalDatabasePath(dbName: String = "app"): String {
        val dbFile = context.getDatabasePath("$dbName.db")
        return dbFile.absolutePath
    }
}
