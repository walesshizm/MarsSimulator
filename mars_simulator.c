/* Mars Kolonisi Yasam Destek Simulatoru
 * Algoritma ve Programlama Odevi - C ile metin tabanli oyun*/
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));   /* Her calistirmada farkli zarlar icin, sadece 1 kez */

    /* ================= 1. DURUM DEGISKENLERI ================= */
    int saglik = 100;
    int enerji = 100;
    int oksijen = 100;
    int su = 0;               /* zorluga gore asagida verilecek */
    int yedekParca = 2;
    int modulHasari = 0;
    int kilitMuhurlu = 0;     /* 0: muhurlu degil, 1: muhurlu */
    int gun = 1;
    int tur = 0;

    /* ================= 2. ZORLUK SECIMI ================= */
    char zorluk;
    int firtinaTur = 0;       /* kum firtinasi kac tur surecek */
    int firtinaHasar = 0;     /* firtinanin bir turdaki temel hasari */
    int esikAyar = 0;         /* kesifte su/parca bulma esigine eklenir */
    int gecerli;

    do {
        printf("Zorluk seciniz (K: Kolay, N: Normal, Z: Zor): ");
        scanf(" %c", &zorluk);
        gecerli = 1;

        switch (zorluk) {
            case 'k': case 'K':
                su = 20; firtinaTur = 3; firtinaHasar = 5; esikAyar = 10;
                break;
            case 'n': case 'N':
                su = 14; firtinaTur = 5; firtinaHasar = 8; esikAyar = 0;
                break;
            case 'z': case 'Z':
                su = 8; firtinaTur = 7; firtinaHasar = 12; esikAyar = -10;
                break;
            default:
                printf("Gecersiz secim! Tekrar deneyin.\n");
                gecerli = 0;
        }
    } while (gecerli == 0);

    printf("\nMars istasyonuna hos geldin! 15 gun hayatta kalmalisin.\n");
    printf("Su: %d | Firtina suresi: %d tur\n", su, firtinaTur);

    /* ================= 3. ANA DONGU ================= */
    char komut;
    int turHarcar;            /* 1: bu komut tur harcar, 0: harcamaz */
    int oyunDurumu = 0;       /* 0: devam, 1: kazandi, 2: kaybetti, 3: Q ile cikti */
    int zar, esik;

    do {
        printf("\nKomut (G: Kesif, O: Oksijen, T: Tamir, D: Durum, U: Uyu, K: Firtina, H: Sifre, Q: Cikis): ");
        scanf(" %c", &komut);
        turHarcar = 1;

        switch (komut) {

            /* ---------- G: KESIF ---------- */
            case 'g': case 'G':
                if (enerji < 15) {
                    printf("Yetersiz enerji! Kesif icin en az 15 enerji gerekir. Komut iptal.\n");
                    turHarcar = 0;
                } else {
                    enerji = enerji - 15;
                    oksijen = oksijen - 10;

                    /* Enerji ve oksijen yuksekse su bulma esigi yuksek */
                    if (enerji > 40 && oksijen > 30) {
                        esik = 60;
                    } else {
                        esik = 30;
                    }
                    esik = esik + esikAyar;

                    zar = rand() % 100;
                    printf("Zar: %d / Su esigi: %d / Parca esigi: %d\n", zar, esik, esik + 20);
                    if (zar < esik) {
                        printf("-> BASARILI: Su buldun! (+6 su)\n");
                        su = su + 6;
                    } else if (zar < esik + 20) {
                        printf("-> Yedek parca buldun! (+1 parca)\n");
                        yedekParca = yedekParca + 1;
                    } else {
                        printf("-> Eli bos dondun.\n");
                    }

                    /* Yaralanma kontrolu */
                    zar = rand() % 100;
                    if (zar < 10 || modulHasari > 70) {
                        printf("Zar: %d / Esik: 10 -> YARALANDIN! (-10 saglik)\n", zar);
                        saglik = saglik - 10;
                    } else {
                        printf("Zar: %d / Esik: 10 -> Yaralanma yok.\n", zar);
                    }
                }
                break;

            /* ---------- O: OKSIJEN URET ---------- */
            case 'o': case 'O':
                if (enerji < 10) {
                    printf("Yetersiz enerji! Oksijen uretimi icin en az 10 enerji gerekir. Komut iptal.\n");
                    turHarcar = 0;
                } else if (su < 2) {
                    printf("Yeterli su yok! En az 2 birim su gerekir. Komut iptal.\n");
                    turHarcar = 0;
                } else {
                    int miktar, artik, kullanilan, uretilen;
                    printf("Kac birim su kullanilsin? (2-%d): ", su);
                    scanf("%d", &miktar);

                    if (miktar < 2 || miktar > su) {
                        printf("Gecersiz miktar! Komut iptal.\n");
                        turHarcar = 0;
                    } else {
                        artik = miktar % 2;                /* tekse 1 birim artik kalir */
                        kullanilan = miktar - artik;
                        uretilen = (kullanilan / 2) * 3;   /* 2 su = 3 oksijen */

                        su = su - kullanilan;
                        oksijen = oksijen + uretilen;
                        enerji = enerji - 10;

                        printf("%d su kullanildi, %d oksijen uretildi.", kullanilan, uretilen);
                        if (artik == 1) {
                            printf(" (1 birim su artik olarak depoda kaldi)");
                        }
                        printf("\n");
                    }
                }
                break;

            /* ---------- T: TAMIR ---------- */
            case 't': case 'T':
                if (yedekParca <= 0) {
                    printf("Yedek parca yok! Tamir yapilamaz. Komut iptal.\n");
                    turHarcar = 0;
                } else if (modulHasari == 0) {
                    printf("Modulde hasar yok, tamire gerek yok. Komut iptal.\n");
                    turHarcar = 0;
                } else if (enerji < 10) {
                    printf("Yetersiz enerji! Tamir icin en az 10 enerji gerekir. Komut iptal.\n");
                    turHarcar = 0;
                } else {
                    int gerekli, onarimTam, harcanan, onarim;

                    /* Hasar seviyesine gore 3 kademe */
                    if (modulHasari <= 30) {
                        printf("Hasar seviyesi: HAFIF\n");
                        gerekli = 1; onarimTam = 20;
                    } else if (modulHasari <= 70) {
                        printf("Hasar seviyesi: ORTA\n");
                        gerekli = 2; onarimTam = 30;
                    } else {
                        printf("Hasar seviyesi: AGIR\n");
                        gerekli = 3; onarimTam = 45;
                    }

                    /* Parca yetmiyorsa elindeki kadarini kullan, onarim orantili azalir */
                    harcanan = gerekli;
                    if (yedekParca < gerekli) {
                        harcanan = yedekParca;
                    }
                    onarim = onarimTam * harcanan / gerekli;

                    yedekParca = yedekParca - harcanan;
                    modulHasari = modulHasari - onarim;
                    enerji = enerji - 10;
                    printf("%d parca harcandi, %d hasar onarildi.\n", harcanan, onarim);
                }
                break;

            /* ---------- D: DURUM RAPORU ---------- */
            case 'd': case 'D':
                printf("\n===== DURUM RAPORU =====\n");
                printf("Gun: %d | Tur: %d\n", gun, tur);
                printf("Saglik: %d | Enerji: %d | Oksijen: %d\n", saglik, enerji, oksijen);
                printf("Su: %d | Yedek parca: %d | Modul hasari: %d\n", su, yedekParca, modulHasari);
                printf("Hava kilidi: %s\n", kilitMuhurlu == 1 ? "MUHURLU" : "muhurlu degil");

                /* Her kritik deger icin ayri uyari */
                if (oksijen < 25) {
                    printf("UYARI: Oksijen kritik seviyede!\n");
                }
                if (saglik < 30) {
                    printf("UYARI: Saglik kritik seviyede!\n");
                }
                if (enerji < 20) {
                    printf("UYARI: Enerji kritik seviyede!\n");
                }
                if (modulHasari > 70) {
                    printf("UYARI: Modul hasari kritik seviyede!\n");
                }

                /* Hepsi guvenliyse tek kosulla normal mesaji */
                if (saglik >= 30 && oksijen >= 25 && enerji >= 20 && modulHasari <= 70) {
                    printf("TUM SISTEMLER NORMAL\n");
                }
                turHarcar = 0;   /* D komutu tur harcamaz */
                break;

            /* ---------- U: UYU / DINLEN ---------- */
            case 'u': case 'U':
                oksijen = oksijen - 5;     /* oksijen tuketimi devam eder */
                enerji = enerji + 25;

                if (oksijen < 20) {
                    printf("Oksijen cok dusuk! Dinlenmek sagligi artirmadi. (-10 saglik)\n");
                    saglik = saglik - 10;
                } else {
                    if (modulHasari > 70) {
                        printf("Modul cok hasarli, rahat uyuyamadin. (+25 enerji, +5 saglik)\n");
                        saglik = saglik + 5;
                    } else {
                        printf("Iyi dinlendin. (+25 enerji, +15 saglik)\n");
                        saglik = saglik + 15;
                    }
                }
                break;

            /* ---------- K: KUM FIRTINASI ---------- */
            case 'k': case 'K':
                if (enerji < 20) {
                    printf("Yetersiz enerji! Firtinaya hazirlanmak icin en az 20 enerji gerekir. Komut iptal.\n");
                    turHarcar = 0;
                } else {
                    int i, carpan, hasar, canEsik, oksEsik, modEsik;
                    int hasarliTur = 0, kayipSaglik = 0, kayipOksijen = 0;

                    enerji = enerji - 20;
                    printf("\n*** KUM FIRTINASI BASLADI (%d tur) ***\n", firtinaTur);

                    for (i = 1; i <= firtinaTur; i++) {
                        /* Cift turlarda ruzgar siddetlenir, hasar 2 kat */
                        if (i % 2 == 0) {
                            carpan = 2;
                        } else {
                            carpan = 1;
                        }
                        hasar = firtinaHasar * carpan;

                        /* Modul cok hasarliysa can kaybi ihtimali artar */
                        canEsik = 25;
                        if (modulHasari > 50) {
                            canEsik = 40;
                        }
                        oksEsik = canEsik + 25;
                        modEsik = oksEsik + 20;

                        zar = rand() % 100;
                        printf("Tur %d (hasar x%d) | Zar: %d / Esikler: %d, %d, %d | ",
                               i, carpan, zar, canEsik, oksEsik, modEsik);

                        if (zar < canEsik) {
                            printf("Yaralandin: -%d saglik\n", hasar);
                            saglik = saglik - hasar;
                            kayipSaglik = kayipSaglik + hasar;
                            hasarliTur++;
                        } else if (zar < oksEsik) {
                            if (kilitMuhurlu == 1) {
                                printf("Hava kilidi muhurlu, oksijen sizintisi atlandi.\n");
                                continue;   /* bu turun geri kalanini atla */
                            }
                            printf("Oksijen sizintisi: -%d oksijen\n", hasar);
                            oksijen = oksijen - hasar;
                            kayipOksijen = kayipOksijen + hasar;
                            hasarliTur++;
                        } else if (zar < modEsik) {
                            printf("Modul hasari: +%d\n", hasar);
                            modulHasari = modulHasari + hasar;
                            hasarliTur++;
                        } else {
                            printf("Firtinadan korundun, zarar yok.\n");
                        }

                        if (saglik <= 0 || oksijen <= 0) {
                            printf("Kritik seviye! Firtina aninda sona erdi.\n");
                            break;   /* donguyu derhal bitir */
                        }
                    }

                    printf("--- Firtina ozeti ---\n");
                    printf("Hasar alinan tur: %d | Kaybedilen saglik: %d | Kaybedilen oksijen: %d\n",
                           hasarliTur, kayipSaglik, kayipOksijen);
                }
                break;

            /* ---------- H: HAVA KILIDI SIFRESI ---------- */
            case 'h': case 'H':
                if (kilitMuhurlu == 1) {
                    printf("Hava kilidi zaten muhurlu. Komut iptal.\n");
                    turHarcar = 0;
                } else if (enerji < 5) {
                    printf("Yetersiz enerji! Sifre denemesi icin en az 5 enerji gerekir. Komut iptal.\n");
                    turHarcar = 0;
                } else {
                    char sifre, giris;
                    int deneme = 0;

                    sifre = 'A' + (gun % 26);   /* sifre gun sayisindan turetilir */
                    printf("Ipucu: Sifre, alfabede A harfinden bugunun gun sayisi kadar ilerideki harftir.\n");

                    do {
                        printf("Sifre (tek harf, deneme %d/3): ", deneme + 1);
                        scanf(" %c", &giris);

                        /* Kucuk harfi buyuk harfe cevir */
                        if (giris >= 'a' && giris <= 'z') {
                            giris = giris - ('a' - 'A');
                        }
                        deneme++;

                        if (giris != sifre) {
                            enerji = enerji - 5;
                            if (enerji < 0) {
                                enerji = 0;
                            }
                            if (giris < sifre) {
                                printf("Yanlis! Ileri git. (-5 enerji)\n");
                            } else {
                                printf("Yanlis! Geri git. (-5 enerji)\n");
                            }
                        }
                    } while (giris != sifre && deneme < 3);   /* iki sart tek ifadede */

                    if (giris == sifre) {
                        kilitMuhurlu = 1;
                        printf("Dogru sifre! Hava kilidi muhurlendi.\n");
                    } else {
                        modulHasari = modulHasari + 20;
                        printf("3 deneme basarisiz! Modul hasari +20. (Dogru sifre: %c)\n", sifre);
                    }
                }
                break;

            /* ---------- Q: CIKIS ---------- */
            case 'q': case 'Q':
                printf("Oyundan cikiliyor...\n");
                oyunDurumu = 3;
                turHarcar = 0;
                break;

            /* ---------- TANIMSIZ KOMUT ---------- */
            default:
                printf("Tanimsiz komut! Tur harcanmadi.\n");
                turHarcar = 0;
        }

        /* ================= ZAMAN AKISI ================= */
        if (turHarcar == 1) {
            tur = tur + 1;
            if (tur % 3 == 0) {          /* her 3 turda bir yeni gun */
                gun = gun + 1;
                oksijen = oksijen - 8;
                printf("\n--- YENI GUN: %d --- (gun basi oksijen -8)\n", gun);
                if (modulHasari > 70) {
                    saglik = saglik - 5;
                    printf("Modul hasari yuksek, saglik -5.\n");
                }
            }
        }

        /* ================= SINIRLANDIRMA (0-100) ================= */
        if (saglik < 0) saglik = 0;
        if (saglik > 100) saglik = 100;
        if (enerji < 0) enerji = 0;
        if (enerji > 100) enerji = 100;
        if (oksijen < 0) oksijen = 0;
        if (oksijen > 100) oksijen = 100;
        if (modulHasari < 0) modulHasari = 0;
        if (modulHasari > 100) modulHasari = 100;

        /* ================= OYUN SONU KONTROLU ================= */
        if (oyunDurumu == 0) {
            if (saglik <= 0 || oksijen <= 0) {
                oyunDurumu = 2;           /* kaybetti */
            } else if (gun > 15) {
                oyunDurumu = 1;           /* 15. gun tamamlandi, kazandi */
            }
        }

        /* Kisa durum satiri */
        if (turHarcar == 1 && oyunDurumu == 0) {
            printf("[Gun %d | Tur %d] Saglik:%d Enerji:%d Oksijen:%d Su:%d Parca:%d Hasar:%d\n",
                   gun, tur, saglik, enerji, oksijen, su, yedekParca, modulHasari);
        }

    } while (oyunDurumu == 0);

    /* ================= SONUC RAPORU ================= */
    int hayattaKalinanGun = gun - 1;   /* tamamlanan gun sayisi */
    int puan = (hayattaKalinanGun * 100) + saglik + oksijen - modulHasari;

    printf("\n========== SONUC RAPORU ==========\n");
    if (oyunDurumu == 1) {
        printf("KAZANDIN! Kurtarma ekibi geldi.\n");
    } else if (oyunDurumu == 2) {
        printf("KAYBETTIN! Hayatta kalamadin.\n");
    } else {
        printf("Oyundan cikis yaptin.\n");
    }
    printf("Hayatta kalinan gun: %d\n", hayattaKalinanGun);
    printf("Toplam tur: %d\n", tur);
    printf("Saglik: %d | Enerji: %d | Oksijen: %d\n", saglik, enerji, oksijen);
    printf("Su: %d | Yedek parca: %d | Modul hasari: %d\n", su, yedekParca, modulHasari);
    printf("PUAN = (%d x 100) + %d + %d - %d = %d\n",
           hayattaKalinanGun, saglik, oksijen, modulHasari, puan);

    return 0;
}
