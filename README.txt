# Readme
ในโปรเจ็คนี้เป็นการใช้ ESP32 dev board ต่อกับ sensor MQ2 เพื่อเก็บข้อมูลการวัดแก๊สในอากาศ โดยมีสมมุติฐานว่ากลิ่นขยะอาจจะมีแก๊สบางอย่างที่ sensor นี้ปนอยู่ด้วย และอาจใช้พัฒนาต่อเป็นระบบ sensor หลายตัวเพื่อการวัดที่หลากหลายมากขึ้น โดยเราจะต่อวงจร ESP32 เพื่อรับค่าจาก MQ2 และส่งข้อมูลไปยัง AWS IoT Core และสร้าง Rule เพื่อบันทึกข้อมูลไปยัง AWS DynamoDB 

Wiring diagram สามารถดูได้จาก ref [1] โดยได้เลือกใช้เพียงการต่อแบบ analog เพราะต้องการค่าการเปลี่ยนแปลงของ sensor

ตัว code สำหรับ ESP32 สามารถดูได้จาก esp32_mq1/esp32_mq1.ino ซึ่งสามารถเปิดดูได้จากโปรแกรม Arduino 

โดยได้ทำการ export ข้อมูลจาก DynamoDB ออกไปยัง fileserver AWS S3 และ  download ข้อมูลออกมา plot ด้วย Jupyter Notebook (python) ใน read_data.ipynb

การเชื่อมต่อ ESP32 กับ AWS รวมทั้ง DynamoDB สามารถศึกษาได้จาก ref [2][3]


# References
[1] ESP32 Gas Sensor
https://esp32io.com/tutorials/esp32-gas-sensor

[2] เชื่อมต่อโหนด MiniLink(ESP32) กับ AWS IoT Core โดยเครือข่าย WiFi / LoRaWAN และ NB-IoT
https://visitwnk.medium.com/ep-1-%E0%B9%80%E0%B8%8A%E0%B8%B7%E0%B9%88%E0%B8%AD%E0%B8%A1%E0%B8%95%E0%B9%88%E0%B8%AD%E0%B9%82%E0%B8%AB%E0%B8%99%E0%B8%94-minilink-esp32-%E0%B8%81%E0%B8%B1%E0%B8%9A-aws-iot-core-%E0%B9%82%E0%B8%94%E0%B8%A2%E0%B9%80%E0%B8%84%E0%B8%A3%E0%B8%B7%E0%B8%AD%E0%B8%82%E0%B9%88%E0%B8%B2%E0%B8%A2-wifi-lorawan-%E0%B9%81%E0%B8%A5%E0%B8%B0-nb-iot-b0d209406634

[3] มาเล่น AWS IoT กันเถอะ EP.3 Rule engine & Rule action
https://iamteam.me/%E0%B8%A1%E0%B8%B2%E0%B9%80%E0%B8%A5%E0%B9%88%E0%B8%99-aws-iot-%E0%B8%81%E0%B8%B1%E0%B8%99%E0%B9%80%E0%B8%96%E0%B8%AD%E0%B8%B0-ep-3-rule-engine-rule-action-db583213f84d