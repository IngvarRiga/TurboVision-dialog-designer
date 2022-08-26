# TurboVision dialog designer

Спасибо авторам:

Дизайнер диалогов, основанный на портированной библиотеке [Turbo Vision](https://github.com/magiblot/tvision)

При сохранении в JSON используется [JSON for Modern C++](https://github.com/nlohmann/json/releases)

#### To compile with English resources, use the definition when building the project.
``````
#define ENG
``````

## Краткое описание

Проект создан для облегчения формирования диалоговых окон, при использовании библиотеки TurboVision при создании консольных приложений. Я не ставил перед собой цель создать многофункциональный программный продукт, а просто решил некоторым образом облегчить себе жизнь при работе над одной из собственных задач. В связи с этим - не ожидайте, что данный редактор будет обновляться очень часто и вообще будет постоянно в активном развитии.

Реализованный на сегодняшний момент вариант практически полностью удовлетворяет моим потребностям, хотя, имея перед собой пример, как можно реализовать подобное (например дизайнер диалогов TV от L. David Baldwin) я понимаю, что совершенству нет предела... Но эта программа - только "гаечный ключ" и ничего более. Таким образом - постоянная ее доработка и наращивание функционала не планируется. Хотя и вполне вероятна.

Код проекта является неорганизованным и не оптимизированным, поскольку писался на коленке в спешке. Будет или нет производится его нормализация - не знаю.

Исходя из сказанного и как я обещал автору портированной библиотеки, указанной выше, я выкладываю исходный код проекта в открытый доступ. Если кто желает использовать данный код, для того чтобы доработать программу, улучшить ее функционал - используйте.

Буду благодарен за упоминание моего скромного вклада, если кто-нибудь будет использовать мой код в своих проектах, а также за любую помощь в написании проекта, документировании программы и локализации на другие языки если найдутся на это желающие.

## А теперь немного о самом проекте:

 - собран с использованием MS Visual Studio 2019 Community Edition;
 - позволяет использовать локализацию интерфейса не "на лету", но все же. Для этого используйте файл multilang.h и задавайте соответствующую константу при сборке проекта;
 - библиотеку TurboVision ищите по ссылке вверху (собранная бибилиотека/заголовки есть внутри проекта);
 - библиотеку nlohmann::json ищите по ссылке вверху (рабочая версия есть внутри проекта);
 - проверка под Linux не производилась, изначально проект был разработан с использованием TDM MinGW C++ x64 c++14, но по некоторым причинам перенесен в MS VC, тем не менее должен собираться и в Linux;
 - программа должна запускаться от имени администратора иначе с высокой вероятностью будет виснуть;
 - после запуска программа отображает только "палитру компонентов", помеченную в заголовке "D&D". Все как всегда, зажали компонент левым кликом мыши и тащите куда надо, и там бросайте. Над каким окном бросили туда и попадет, несмотря ни на что. Бросили над "desktop" - отменили операцию;
 - никаких окон по умолчанию не создается, используйте меню/горячие клавиши;
 - программа позволяет использовать механизм Drag&Drop для компонентов, которые полностью реализованы в дизайнере, т.е. создание, настройка и генерация кода;
 - кроме Drag&Drop в созданном диалоговом окне есть контекстное меню, вызываемое по клику на знаке "=" на левой границе окна;
 - сохранение разрабатываемых диалогов производится **только** в формате JSON;
 - имеющаяся возможность чтения *.DLG используется только для переноса старых разработанных диалогов и НЕ совместима со стандартными ресурсными файлами TurboVision. И вскоре будет удалена совсем;
 - и да, программа позволяет редактировать одновременно несколько диалогов.

## Кратко по редактированию:

- **Ctrl+N** - создать новый диалог (можно несколько одновременно);
- компонент становится выделенным, когда по нему кликнут (красный цвет) (для TListBox/TMemo пока не работает, но они все равно становятся "выделенными");
- перемещение компонента по форме - кликнув и зажав левую клавишу мыши;
- изменение размеров - кликнув и зажав левую кнопку мыши на правом нижнем углу компонента (или просто на правом для TInputLine, например, поскольку он однострочный);
- двойной клик на компоненте - вызов его настроек;
- правый клик - контекстное меню компонента;
- **Ctrl+Del** - удаляет выделенный красным компонент (есть плавающая ошибка, при которой крайне редко удаляются не только красный компонент, но и несколько других, пытаюсь найти, замечено только при удалении строки ввода);
- двойной клик по пустому месту в диалоге - вызов свойств самого диалога;
- **Alt+C** - выравнивание размера текущего диалога по его содержимому;
- **F9** - тестирование диалога.
- **F2** сохранение диалога с тем же самым именем с каким был загружен, либо, если вновь созданный - задается имя;
- **Shift+F2** - сохранить диалог как...;
- **Ctrl+Ins** / **Shift+Ins** - взять в буфер текущий элемент / вставитт из буфера;

Самое главное: Alt+X - мгновенно закрывает программу, даже если вы не сохранили измененные диалоги - никаких вопросов задано не будет. Да, это неправильно, я знаю. Пока руки не дошли :)

Все остальное - смотрите на указанные в меню короткие клавиши.

## Планы, которые могут быть реализованы, а могут и нет
---
Сразу оговорюсь: то что здесь перечислено - это просто то, чего мне в свое время так не хватало или то, что пришло в голову по результатам собственной тестовой эксплуатации. Но учитывая, что данный проект - просто хобби, помогающее основному направлению деятельности - **ждать, что будет реализовано написанное не стоит**. Можете присоединиться и дописать сами. Как уже говорил - буду рад помощи.

- [ ] индикатор сохранения диалога на границе окна;
- [ ] добавление редактора свойств или хотя бы его отображение для удобства;
- [ ] добавление TListBox / TMemo в "палитру" компонентов;
- [ ] реализация дополнительных компонентов как отдельной расширяемой библиотеки;
- [ ] переделка базовых компонентов с "выравниванием" API для нормального доступа к функциям и полям, имеющим стандартизированные имена и упорядоченные модификаторы доступа, а не как бог на душу положил в случае стандартной библиотеки;
- [ ] дизайнер меню;
- [ ] дизайнер цветовых схем для использования различными компонентами, поскольку реализацию палитр сделанную в базовой версии считаю убогой и неудобной (могу ошибаться);

## Известные проблемы
---
- да, свойства и прочие настройки TMemo/TListBox не реализованы и когда будут - не знаю, поскольку сам я их пока что не использую, понимаю, что стоило бы доделать до конца, однако и без того пришлось переопределять практически всю ветку объектов, короче пока нет времени. Если кто захочет - пишите, я подскажу что делать;
- в коде программы для парирования ошибок загрузки JSON используется конструкция try/catch, которая на сколько мне известно не работает или работает криво в Linux. Печально, но это проблемы самого Linux и его компиляторов. Проверять самому нет времени и желания, если есть кто-то кто хочет исправит/поправить - пишите сразу решение, я сам разбираться не буду - нет времени.
- компиляция CMake под Windows через gcc работает но программа не запускается. Непонятно почему?

## Последние изменения
##### (последние изменения всегда вверху списка, не нужно листать)
---
### 26.08.2022
- [x] Исправлена ошибка сохранения имени базового класса диалога при редактировании его свойств;
- [x] Генерация #define Uses_ ... содержит только необходимые элементы;
- [x] При генерации исходного кода автоматически формируются шаблоны функций setData/getData и обработчик событий

### 25.08.2022
- [x] Добавлена генерация заголовка при создании исходного кода диалога.

### 24.08.2022
- [x] Текущий релиз рабочий в части стандартных компонентов.

### 08.08.2022
- [x] Обнаружены новые ошибки в TInputLong... печально, пытаюсь исправить;
- [x] Добавлено окно редактирование свойств TInputLong;
 
### 05.08.2022
- [x] В палитру компонентов добавлен TInputLong / TInputDouble. TInputLong реализован, см. в textrainput.cpp. Предназначен для ввода любых целых чисел от LONG_MIN до LONG_MAX. TInputDouble - пока не реализован (предполагается редактирование long double). Редактор свойств в процессе доделки;
- [x] При проектировании диалога TInputLine содержит "ABC", TInputLong - "123"/ TInputDouble - "1.2" чтобы отличать где какой тип полей, а то уже сам путаюсь;
- [x] Для использования TInputLong используйте в своём проекте исходный код textrainput.cpp / textrainput.h

### 27.07.2022
- [x] Небольшая очистка кода;
- [x] Сделан компонент редактирования целых чисел (в палитре пока что нет);
- [x] Сделан CMakeLists.txt (mingw.cmd предназначен для автоматической сборки mingw компилятором в Windows) правильно или нет - неважно учусь пока что использовать. Если есть желание сделать "как надо" не стесьняйтесь предлагайте свое решение. Программа компилируется по умолчанию с Русскими ресурсами. Для использования английских откорректируйте CMakeLists.txt строку
```
#use Russian (RUS) or English (ENG) resource string
add_definitions(-DRUS)
```

### 17.06.2022
- [x] Доделано окно редактирования свойств TDialog, исходный код генерируется согласно настройкам
- [x] С учётом дальнейшей доработки исходный код диалога теперь сохраняется в файл с расширением ***.src**

### 16.06.2022
- [x] Исправлена идиотская ошибка сохранения исходного файла диалога, при которой исходный код содержимого не генерировался!
- [x] Переделано (пока что не полностью) окно редактирования свойств диалога. Сейчас можно задавать флаги окна.

### 06.06.2022
- [x] Исправлен вызов окна сохранения диалога при закрытии через кнопку закрытия окна. Ранее вызывалось не сохранение а окно свойств диалога.

### 24.05.2022
- [x] Откорректирован вызов контекстного меню диалога, согласно предложениям [magiblot](https://github.com/magiblot/tvision). Однако меню все равно вызывается только при отпускании правой клавиши :) (извините, как привык...)

### 12.05.2022
- [x] Исходный код работы со TStremableClass исключен из проекта

### 26.04.2022
- [x] **Внимание!  Звгрузка и выгрузка из/в ресурсы DLG исключено полностью!** 
- [x] Исправления в интерфейсе контекстных меню;

### 24.04.2022
- [x] Исправлена ошибка редактирования TRadioButtons/TCheckBoxes; 
- [x] Исправлена ошибка авторазмера диалога; 

### 21.04.2022
- [x] Корректировка алгоритма сохранения файлов. Теперь все диалоги по умолчанию сохраняются в JSON. F2 - сохранить, Shift+F2 - сохранить как; 
- [x] Загрузка из файлов ресурсов лишена коротких клавиш;
- [x] **ВНИМАНИЕ! Сохранение в ресурсных файлах - исключено из алгоритма как устаревшее, теперь только в JSON**;

### 20.04.2022
- [x] **ВНИМАНИЕ! Начиная с этой версии сохранение в виде ресурсов категорически не рекомендуется. Данная возможность будет окончательно удалена из программы как только я переведу все свои наработки (немногочисленные, к слову сказать) в формат JSON**;
- [x] Реализовно Copy/Paste (Ctrl+Ins / Shift+Ins) компонентов внутри диалога и между редактируемыми диалогами. Даже если скопируете и закроете диалог, буфер обмена будет содержать скопированный элемент, который переносится как описание в JSON формате. Перенос объектов - по одному! Никаких групповых переносов (... ну по крайней мере пока что :) );
- [x] Исправление некоторых найденных ошибок; 
- [x] Небольшой рефакторинг/оптимизация кода; 

### 06.04.2022
- [x] Добавлена функция тестирования текущего диалога (просто пересоздание на основе стандартных компонентов и отображение в модальном режиме);

### 05.04.2022
- [x] Добавлена функция автоматического подбора размера диалога (в основном меню программы). Функция смотрит правую и нижнюю границы компонентов в окне и выравнивает размеры диалогового окна;

### 01.04.2022
- [x] Сделан первый вариант сохранения в JSON,(сохраняются только: TDialog, TInputLine, TButton, TStaticText, TCheckBoxes, TRadioButtons, TMemo, остальное пока нет :) );
- [x] Исправлены замеченные мелкие ошибки;

### 07.02.2022
- [x] Код диалога генерируется в том порядке, в котором произошла вставка компонентов в окно
- [x] Добавлена возможность (опция) центрирования диалоговых окон в настройках TDialog Properties, которая, однако, не сохраняется пока в ресурсах, поскольку сейчас мне важна именно совместимость этих ресурсов с этим редактором из другого проекта;

### 02.02.2022
- [x] Правка генерации кода TMemo / TListBox
- [x] Изменен цвет кнопки контекстного меню диалога стал черный на ярко зеленом фоне

### 01.02.2022
- [x] Откорректировано поведение Drag&Drop компонентов, теперь если промахиваешься мимо конкретного окна программа проверяет попадание в другие окна, и если куданибудь попадает - вставляет компонент туда. Хорошо или плохо - решать вам. Сделано для одновременного редактирования нескольких окон;
- [x] При вставке компонента через Drag&Drop диалог, в который вставляется компонент сразу становится активным (это играет роль когда вы пытаетесь сразу изменить размеры или положение брошенного компонента, не приходится делать лишний клик);
- [x] Увеличина длина вставляемого TInputLIne;

### 31.01.2022
- [x] Переделана функция изменения размеров компонентов. Теперь изменять размеры компонента нужно кликнув по правому нижнему углу компонента (или просто по правому, если компонент однострочный);
- [x] Добавлено контекстное меню, вызываемое по правому клику мышкой на компоненте. Меню содержит разное количество пунктов для разных компонентов. Но стандартными являются - вызов редактора свойств (эквивалентен двойному клику по компоненту) и удаление компонента (в отличие от нажатия на Ctrl+Del -> Удаляется компонент для которого вызвано меню!) Свойства TMemo/TListBox пока что не реализованы;
- [x] Для TStaticText/TButton доступен пункт выпадающего меню: авторазмер по содержимому, который выравнимает размер компонента по введенному тексту, даже вроде как с учетом Unicode... правда перерисовывает его порой не сразу а при последующем наведении мыши, не пойму в чем проблема;
- [x] При простом перемещении курсора мыши по заштрихованной области редактируемого диалога текущая позиция мыши (символ) подсвечивается зеленым. Данная подсветка пропадает если навести курсо на компонент и автоматически появляется снова при перемещении мыши на заштрихованную область. Мне просто очень потребовался данный указатель :);
- [x] Выпадающее меню диалога теперь возникает только при отпускании правой кнопки мыши на заштрихованном поле;

### 28.01.2022
- [x] Исправлено сохранение в ресурсах при добавлении TCheckBoxes / TRadioButton;
- [x] Контекстное меню редактируемого диалога, вызываемое по правому клику мышки на пустом месте диалога;
- [x] Вставить TMemo можно через контекствное меню диалога, код генерируется (свойства пока что не редактируются);
- [x] Вставить TListBox можно через контекствное меню диалога, код генерируется (свойства пока что не редактируются);
- [x] При использовании выпадающего меню диалога вставка компонентов производится в точку клика правой кнопкой мыши;
- [x] Исправлено действие сохранения диалога, при закрытии через кнопку на окне;
- [x] Изменен состав меню диалога, вызываемого по нажатию на "=";
