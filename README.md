# PAT- Simple Eventbased Webserver

## Mengukur Kinerja Web Server

Pada tugas ini dilakukan dua percobaan yaitu melakukan 10.000 request konkuren sebuah dokumen HTML berukuran kurang lebih 500 bytes, dan dokumen HTML berukuran kurang lebih 20 KB. Percobaan dilakukan pada dua jenis server yaitu Web server Apache dan Web Server Nginx.

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

```
Give an example
```
Berikut adalah hasil yang didapatkan saat mengakses dokumen HTML berukuran 20 kilobytes:

### And coding style tests

Explain what these tests test and why

```
Give an example
```

## Deployment

Add additional notes about how to deploy this on a live system

## Built With

* [Dropwizard](http://www.dropwizard.io/1.0.2/docs/) - The web framework used
* [Maven](https://maven.apache.org/) - Dependency Management
* [ROME](https://rometools.github.io/rome/) - Used to generate RSS Feeds

## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags). 

## Authors

* **Billie Thompson** - *Initial work* - [PurpleBooth](https://github.com/PurpleBooth)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Hat tip to anyone who's code was used
* Inspiration
* etc