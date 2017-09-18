# PAT- Simple Eventbased Webserver

## Mengukur Kinerja Web Server

Pada tugas ini dilakukan dua percobaan yaitu melakukan 10.000 request konkuren sebuah dokumen HTML berukuran kurang lebih 500 bytes, dan dokumen HTML berukuran kurang lebih 20 KB. Percobaan dilakukan pada tiga jenis server yaitu Web server Apache, Web Server Nginx, dan Web Server sederhana dengan pendekatan event-based.

### Tool Benchmark

Kakas yang digunakan untuk percobaan adalah ApacheBench (ab). Sebuah program open source yang dikembangkan untuk mengukur kinerja HTTP web server. ApacheBench termasuk dalam Apache Web Server sehingga tidak perlu diinstal secara terpisah.

Berikut adalah penggunaan ApacheBench pada percobaan:

```
ab -n x -c y [http[s]://]hostname[:port]/path
```
Dimana,
* n x : ab akan mengirim x request kepada server
* c y : ab akan mengirim y request pada saat yang sama setiap waktunya


Maka untuk melakukan pengukuran kinerja pelayanan 10.000 request konkuren ApacehBench dipanggil seperti dibawah ini:

```
ab -n 10000 -c 10000 http[s]://]hostname[:port]/path
```

## Hasil Percobaan

Percobaan dilakukan pada lingkungan Ubuntu

### Apache2

Berikut adalah hasil yang didapatkan saat mengakses dokumen HTML berukuran 500 bytes:
![alt text](image/500b-apache.png)


Berikut adalah hasil yang didapatkan saat mengakses dokumen HTML berukuran 20 kilobytes:
![alt text](image/20kb-apache.png)

### Nginx

Berikut adalah hasil yang didapatkan saat mengakses dokumen HTML berukuran 500 bytes:


Berikut adalah hasil yang didapatkan saat mengakses dokumen HTML berukuran 20 kilobytes:


### Simple Event-based Web Server 

Berikut adalah hasil yang didapatkan saat mengakses dokumen HTML berukuran 500 bytes:


Berikut adalah hasil yang didapatkan saat mengakses dokumen HTML berukuran 20 kilobytes:

## Instalasi dan Cara Penggunaan Simple Event-based Web Server 

Simple Event-based Web Server dibangun dengan bahasa C menggunakan socket dan library libev. Untuk percobaan ini, server hanya dapat menerima request file dengan extension HTML.

Kompilasi program dengan menjalankan Makefile

```
make
``` 
Untuk menjalankan server

```
./server [port] [lokasi file html] [& - menjalankan server sebagai background process]
```

Pada percobaan ini, telah disediakan file untuk serving yaitu pada folder html yang berisi dua file HTML berukuran 500 bytes (index.html) dan 20kb (index2.html) sehingga pada defaultnya server dijalankan seperti berikut:

```
./server [port] ./html [& - menjalankan server sebagai background process]
```

## Oleh

* Elvina R. K. Situmorang - 13514045
* Atika Azzahra Akbar - 13514077

## Referensi

* Hat tip to anyone who's code was used
* Inspiration
* etc