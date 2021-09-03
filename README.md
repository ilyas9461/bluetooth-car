<h1 align="center">Bluetooth Kontrollü Arduino Araba </h1>


## Giriş

Arduino UNO ile yapılmış bluetooth kontrollü araba çalışması. Arabanın mekanik kısımları forex malzemeden yapılmıştır.
Forex malzeme el ile işlemesi kolay olduğu için tercih edilmiştir. Bir falçata yardımıyla kolayca şekil verilebilir.


## Çalışma Şekli

Cep telefonuna google play üzerinden indirilen bir bluetooth kontrol programı yardımıyla kolayca çalıştırılabilir. Biz
Bluetooth RC Controller programını kullandık. Ön ve arkada iki adet mesafe sensörü ile engeller algılanabilmektedir. 
Ön tarafta ultrasonik sensör servo motor ile 120 deerecelik açıyı tarayabilmektedir. Öne yada arkaya engel geldiğinde 
araba otomatik olarak durmaktadır. Motor sürücü devresi olarak L298 modülünü kullandık. Cep telefon üzerinden gönderilen
komutlar  bluetooth modül ile UNO ya seri olarak gönderilmektedir. Tanımlanan komutlara göre araba uygun hareketleri yapmaktadır.

Yazılım üzerinde gerekli tanımlamlar ve açıklamalar yapılmıştır. Daha ayrınrılı bilgi için yazılımı inceleyebilirsiniz.


## Kullanılan Teknolojiler

```bash
- Arduino UNO programlama.
- Ultrasonik ve Infrared Hareket algılama.
- DC ve Servo Motor yön kontrolü.

```

## Örnek çalışma videosu :

[![](https://camo.githubusercontent.com/241d4106ff5edca2ee25e04dcf4546fad9d20b626f7a10990307e8f83e95459f/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f796f75747562652d2532334646303030302e7376673f267374796c653d666f722d7468652d6261646765266c6f676f3d796f7574756265266c6f676f436f6c6f723d7768697465253232)](https://youtu.be/TXWfKeDM5Kk)

## İletişim

- GitHub [@your-ilyas9461](https://github.com/ilyas9461)
- Linkedin [@your-linkedin](https://www.linkedin.com/in/ilyas-yağcioğlu-6a6b17217)
