# ESP32CAM

### ESP32 dibuat oleh Espressif Systems, perusahaan berbasis di Shanghai, Tiongkok. ESP32Cam berfungsi sebagai mikro controller dan sebagai kamera.ESP32-CAM hadir dengan tiga pin ground (GND) dan dua pin daya: 3.3V dan 5V. Namun kami merekomendasikan dengan menggunakan daya input 5V. ESP32Cam dapat dikontrol atau di program melalui software ArduinoIDE.
___

#### Berikut langkah-langkah untuk menjalankan ESP32Cam
1. Install terlebih dahulu sorftware ArduinoIDE di link berikut ini : 
https://www.nesabamedia.com/download-arduino-ide/  *(for windows)*
2. Buka Aplikasi Arduino IDE. Lalu masukkan beberapa file library masing masing prooject yang telah di download pada Arduino IDE. __(Sketch -> Include Library -> Add .Zip library)__
![Include Library](foto/Library.png)
3. Pastikan telah terinstal library ESP32 Board.  Jika belum, masukkan URL esp32.json pada Preference Arduino IDE. Caranya, buka Arduino IDE, lalu pilih __FILE -> PREFERENCES__. Lalu masukkan URL (https://dl.espressif.com/dl/package_esp32_index.json) ke kolom __Additional Boards Manager URLs__ seperti gambar dibawah ini :
![Preference](foto/Preferances.png)Jika sebelumnya sudah terdapat URL untuk ESP8266, tambahkan jeda (koma) seperti pada konfigurasi dibawah. 
> https://dl.espressif.com/dl/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json
4. Setelah URL ditambahkan maka selanjutnya ke menu __Tools -> Board -> Boards Manager__ lalu cari __esp32 by Espressif Systems__ seperti gambar dibawah.  
**Pastikan terkoneksi internet*
![Boards_Manager](foto/board.png)
5. Untuk mengupload file pastikan ESP32Cam berada pada mode flash. Berikut wiring diagram untuk mode flash
![Mode Flash](foto/config.png)
6. Karena ESP32Cam tidak dilengkapi port untuk menguhubungkan ke PC program, maka diperlukan USB TTL tambahan.
7. Jika memakai __downloader ttl CH340__, maka silahkan download terlebih dahulu driver ch340 : https://sparks.gogo.co.nz/ch340.html . Namun jika menggunakan __ftdi ttl (merah)__ menggunakan driver FT32R berikut : https://www.usb-drivers.org/ft232r-usb-uart-driver.html .
8. Jika sukses, maka lepas GPIO 0 yang sebelumnya menyambung dengan GND. Lalu masuk Serial Monitor dan tekan tombol reset pada ESP32CAM.
___