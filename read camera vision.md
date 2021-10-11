# Camera Vision
## Langkah-langkah menjalankan Camera Vision
### Langkah-langkah untuk menjalankan program Camera Vision
1. Siapkan ESP32Cam seperti yang telah dijelaskan diawal
[ESP32Camera](google.com) (dalam kurung google.com diganti link dimana read esp32cam.md di upload di github)
2. Download Libraries yang dibutuhkan disini :
https://drive.google.com/file/d/1CLGPRt8_l0wwoNG6AWUamMlCOkm427ZJ/view . Ekstrak .ZIP pada suatu folder.
3. Lalu Buka program .ino yang ada pada __library example__ seperti yang tercantum dalam gambar dibawah.
![Example](foto/Library.png)
4. Lalu ganti pengaturan Wifi pada sketch program yang telah didownload seperti pengaturan ssid dan password.
![Pengaturan Wifi](foto/Wifi.png)
5. Pilih Board AI Thinker ESP32CAM pada modul Board Arduino IDE. Pilih Baudrate 115200 untuk Serial Monitor.
![Board](foto/Tools.png)
![Serial Mpnitor](foto/monitor.png)
6. Copy IP address ESP32CAM tersebut pada sebuah Browser. Lalu Pilih Start Stream pada tombol merah dibawah. 
![Start Stream](foto/stream.png)
![Ready to use](foto/ready.png)
*untuk resolusi dapat diatur sesuai dengan kecepatan internet yang digunakan

### Langkah-langkah untuk menjalankan hardware Camera Vision
1. Setelah ESP32Cam telah selesai di program maka cabut ESP32Cam dari USB, Kemudian hubungkan dengan adaptor 5V seperti berikut : 
![Adaptor](foto/depan.jpeg) 
![Adaptor](foto/Belakang.jpeg)
2. Untuk pin Vin (5V) dihubungkan ke positif(kabel merah) dan untuk pin GND dihubungkan ke ground (kabel hitam)
**hati-hati ketika menyolder jangan ada bagian yang terhubung agar tidak terjadi short*
3.untuk pemaketannya kurang kebih seperti gambar dibawah ini : 
![Camera Vision](foto/camvision.jpeg)
____