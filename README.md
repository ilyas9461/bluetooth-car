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

<a href="https://www.youtube.com/watch?v=TXWfKeDM5Kk&t=22s" target="_blank">
     <img src="./DOC/youtube.png" alt="youtube" width="55">
</a>

## İletişim

- GitHub [@your-ilyas9461](https://github.com/ilyas9461)
- Linkedin [@your-linkedin](https://www.linkedin.com/in/ilyas-yağcioğlu-6a6b17217)
