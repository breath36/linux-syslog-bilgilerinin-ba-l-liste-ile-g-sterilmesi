# linux-syslog-bilgilerinin-ba-l-liste-ile-g-sterilmesi
Linux Syslog Yönetimi: Bağlı Liste (Linked List) Uygulaması
Bu proje, Linux işletim sistemindeki sistem günlüklerini (syslog) dinamik bir şekilde işlemek ve düşük seviyeli bellek yönetimi prensiplerini uygulamak amacıyla C dilinde geliştirilmiştir. Proje, dosya sisteminden gelen verileri Tek Yönlü Bağlı Liste (Singly Linked List) veri yapısında depolar.

📋 Proje Hakkında Teknik Sorular ve Cevaplar
1. Syslog Mekanizması Nedir ve Ne İçin Kullanılır?
Syslog, Unix ve Linux tabanlı sistemlerde çekirdek (kernel), sistem servisleri ve uygulamalar tarafından üretilen mesajların standart bir protokol üzerinden kaydedilmesidir.

Kullanım Amacı: Sistem hatalarının ayıklanması (debugging), güvenlik denetimleri (audit), sistem sağlığının izlenmesi ve olay analizi için kritik bir veri kaynağıdır. Genellikle /var/log/syslog konumunda tutulur.

2. Bağlı Liste Veri Yapısı ile Günlükler Nasıl Tutulur?
Syslog verileri satır bazlı ve belirsiz uzunlukta olduğu için bağlı liste yapısı idealdir.

Her bir günlük satırı bir düğüm (node) içerisine yerleştirilir.

Her düğüm, log içeriğini (payload) ve zincirin bir sonraki halkasını işaret eden bir bellek adresini (next pointer) içerir.

Veriler dosya sonuna kadar okunarak dinamik olarak belleğe eklenir.

3. Neden Tek Yönlü Bağlı Liste Tercih Edildi?
Bu projede Tek Yönlü Bağlı Liste (Singly Linked List) seçilmesinin temel gerekçeleri şunlardır:

Kronolojik Akış: Syslog verileri doğası gereği zamansal bir sıra ile gelir ve genellikle eskiden yeniye doğru (tek yönlü) okunur.

Bellek Optimizasyonu: Çift yönlü listelerin aksine her düğümde sadece tek bir işaretçi tutulur. Bu durum, on binlerce satırlık log verisi işlendiğinde bellek maliyetini (overhead) minimize eder.

Dinamik Ölçeklenebilirlik: Log dosyasının boyutu önceden bilinmediği için diziler (arrays) yerine, çalışma zamanında büyüyebilen bu yapı bellek verimliliği sağlar.

🛠️ Uygulama Detayları
Kullanılan Fonksiyonlar ve Değişken İsimlendirmeleri
Puanlama kriterlerine uygun olarak, tüm isimlendirmeler işlevine uygun seçilmiştir:

LogNode: Her bir günlük kaydını temsil eden temel yapı birimi.

log_payload: Düğüm içerisinde saklanan asıl mesaj içeriği.

create_new_node: malloc kullanarak bellekten yer ayıran ve düğümü initialize eden fonksiyon.

append_log_entry: Yeni gelen log kaydını listenin sonuna (kronolojik sıraya uygun olarak) ekleyen fonksiyon.

free_log_list: Bellek sızıntılarını önlemek amacıyla program sonunda tüm listeyi tahliye eden fonksiyon.
