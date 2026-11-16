# MarsSimulator

# 🚀 Mars Kolonisi – Yaşam Destek Simülatörü

C programlama dili kullanılarak geliştirilen, oyuncunun Mars'taki bir uzay istasyonunda 15 gün boyunca hayatta kalmaya çalıştığı metin tabanlı bir hayatta kalma simülasyonu.

Oyuncu; sağlık, enerji, oksijen, su ve yedek parça gibi kaynakları dengeli yöneterek kum fırtınaları, istasyon hasarları ve beklenmedik olaylarla mücadele eder. Amaç, kaynakları doğru kullanarak kurtarma ekibi gelene kadar hayatta kalmaktır.

## 📌 Proje Hakkında

Bu proje, Algoritma ve Programlama dersi kapsamında C programlama diliyle geliştirilmiştir.

Oyunda oyuncunun verdiği her karar hayatta kalma sürecini etkiler. Keşif yapmak, oksijen üretmek, istasyonu tamir etmek veya dinlenmek gibi eylemler farklı kaynakların tüketilmesine ya da yenilenmesine neden olur.

Rastgele olay mekanikleri sayesinde her oyun deneyimi birbirinden farklı olabilir.

## 🎮 Özellikler

- **Kaynak Yönetimi:** Sağlık, enerji, oksijen, su ve yedek parça kaynaklarını yönetme.
- **Zorluk Seviyeleri:** Kolay, Normal ve Zor olmak üzere üç farklı zorluk seçeneği.
- **Rastgele Olaylar:** Keşif ve kum fırtınalarında rastgele sayı üretimiyle belirlenen sonuçlar.
- **Keşif Sistemi:** Mars yüzeyinde keşif yaparak su veya yedek parça bulma.
- **Oksijen Üretimi:** Su tüketerek oksijen üretme.
- **Tamir Mekaniği:** Hasar gören istasyonu yedek parçalar kullanarak onarma.
- **Kum Fırtınaları:** İstasyonun farklı sistemlerine zarar verebilen çok turlu fırtınalar.
- **Şifre Sistemi:** Hava kilidini mühürlemek için ipuçlarına dayalı şifre bulmacası.
- **Durum Raporu:** İstasyonun mevcut kaynaklarını ve kritik uyarıları görüntüleme.
- **Puanlama Sistemi:** Hayatta kalınan gün, sağlık, oksijen ve modül hasarına göre final puanı hesaplama.

## ⚙️ Zorluk Seviyeleri

Oyuna başlamadan önce üç zorluk seviyesinden biri seçilir.

| Özellik | Kolay | Normal | Zor |
|---|---:|---:|---:|
| Başlangıç suyu | 20 | 14 | 8 |
| Kum fırtınası süresi | 3 tur | 5 tur | 7 tur |
| Fırtına temel hasarı | 5 | 8 | 12 |
| Keşif bulma eşiği | +10 | 0 | -10 |

Zorluk seviyesi arttıkça kaynak yönetimi zorlaşır ve hayatta kalmak daha fazla strateji gerektirir.

## 🕹️ Oyun Komutları

Oyun, terminal üzerinden harf tabanlı komutlarla kontrol edilir.

| Komut | İşlev |
|---|---|
| `G` | Keşif yapar, su veya yedek parça bulmaya çalışır. |
| `O` | Su tüketerek oksijen üretir. |
| `T` | Yedek parça kullanarak modül hasarını onarır. |
| `D` | Mevcut kaynakların ve istasyonun durumunu gösterir. |
| `U` | Dinlenerek enerji ve belirli koşullarda sağlık kazanır. |
| `K` | Kum fırtınasına karşı hazırlık yapar ve fırtına sürecini başlatır. |
| `H` | Hava kilidinin şifresini çözerek kilidi mühürler. |
| `Q` | Oyundan çıkar. |

**Not:** `D` komutu ve geçersiz veya gerçekleştirilemeyen bazı işlemler tur harcamaz.

## 🧠 Oyun Mekanikleri

### Kaynak Yönetimi
Oyuncunun sağlık, enerji ve oksijen değerleri 0-100 arasında sınırlandırılmıştır. Su ve yedek parça miktarları ise oyun boyunca değişebilir.

### Keşif Sistemi
Keşif yapmak 15 enerji ve 10 oksijen tüketir. Başarı olasılığı mevcut kaynak seviyelerine ve seçilen zorluk seviyesine bağlıdır.

Keşif sonucunda:
- 6 birim su bulunabilir.
- 1 adet yedek parça bulunabilir.
- Hiçbir kaynak bulunamayabilir.

Ayrıca keşif sırasında yaralanma ihtimali vardır.

### Oksijen Üretimi
Oksijen üretiminde 2 birim su kullanılarak 3 birim oksijen elde edilir. Tek sayıda su girilmesi durumunda kullanılmayan 1 birim su depoda kalır.

### İstasyon Tamiri
Modül hasarı üç seviyede değerlendirilir:

- Hafif hasar: 1 yedek parça ile 20 hasar onarımı.
- Orta hasar: 2 yedek parça ile 30 hasar onarımı.
- Ağır hasar: 3 yedek parça ile 45 hasar onarımı.

Yeterli yedek parça bulunmadığında mevcut parçalarla orantılı onarım yapılır.

### Kum Fırtınası
Kum fırtınaları birden fazla tur boyunca devam eder. Fırtınanın çift numaralı turlarında hasar iki katına çıkar.

Fırtına sırasında rastgele olarak:
- Sağlık kaybı yaşanabilir.
- Oksijen sızıntısı meydana gelebilir.
- Modül hasarı oluşabilir.
- Herhangi bir hasar alınmayabilir.

Hava kilidinin mühürlenmesi, belirli oksijen sızıntısı olaylarının önüne geçer.

### Zaman Sistemi
Her üç turda bir yeni gün başlar. Yeni günün başlangıcında 8 birim oksijen tüketilir.

Oyuncunun hedefi 15 günü tamamlayarak kurtarma ekibinin gelmesini sağlamaktır.

## 🏆 Oyun Sonu ve Puanlama

Oyun iki farklı şekilde sona erebilir:

- **Kazanma:** 15 günlük hayatta kalma sürecinin tamamlanması.
- **Kaybetme:** Sağlık veya oksijen değerinin sıfıra düşmesi.

Oyundan `Q` komutuyla manuel olarak da çıkılabilir.

Final puanı aşağıdaki formülle hesaplanır:

```text
PUAN = (Hayatta Kalınan Gün × 100)
       + Sağlık
       + Oksijen
       - Modül Hasarı
```

## 💻 Kullanılan Teknolojiler

- **Programlama Dili:** C
- **Standart Kütüphaneler:**
  - `stdio.h` – Girdi ve çıktı işlemleri.
  - `stdlib.h` – Rastgele sayı üretimi ve standart yardımcı fonksiyonlar.
  - `time.h` – Rastgele sayı üretecinin zaman tabanlı başlatılması.

## 🛠️ Kurulum ve Çalıştırma

Projeyi bilgisayarınıza klonlayın:

```bash
git clone https://github.com/KULLANICI-ADINIZ/mars-kolonisi-simulatoru.git
```

Proje klasörüne girin:

```bash
cd mars-kolonisi-simulatoru
```

GCC kullanarak derleyin:

```bash
gcc mars_simulator.c -o mars_simulator
```

Programı çalıştırın:

**Windows:**
```bash
mars_simulator.exe
```

**Linux / macOS:**
```bash
./mars_simulator
```

> Derleme işlemi için GCC veya uyumlu bir C derleyicisi gereklidir.

## 📂 Proje Yapısı

```text
mars-kolonisi-simulatoru/
│
├── mars_simulator.c
└── README.md
```

## 📚 Kaynakça ve Yararlanılan Kaynaklar

Projenin geliştirilmesi ve dokümantasyonu sırasında aşağıdaki kaynaklardan yararlanılmıştır:

- **C Programlama Dili:** Standart C kütüphaneleri ve programlama dili dokümantasyonu.
- **ChatGPT (OpenAI):** Algoritma geliştirme sürecinde fikir alışverişi, C programlama konularının açıklanması ve dokümantasyon desteği.
- **Claude (Anthropic):** Algoritma ve programlama sürecinde fikir değerlendirme ve geliştirme desteği.

**Yapay Zekâ Kullanım Beyanı:** ChatGPT ve Claude araçlarından geliştirme sürecinde yardımcı kaynak olarak yararlanılmıştır. Projenin kodu, mantığı ve son düzenlemeleri proje geliştiricisinin sorumluluğundadır.

## 👨‍💻 Geliştirici

Mert SEVİNÇ

Algoritma ve Programlama Dersi Projesi

---

