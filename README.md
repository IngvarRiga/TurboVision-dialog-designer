# TurboVision dialog designer

Дизайнер диалогов, основанный на портированной библиотеке [Turbo Vision](https://github.com/magiblot/tvision)

#### To compile with English resources, use the definition when building the project.
``````
#define ENG 
``````
 
#### Краткое описание

Проект создан для облегчения формирования диалоговых окон, при использовании библиотеки TurboVision при создании консольных приложений. Я не ставил перед собой цель создать многофункциональный программный продукт, а просто решил некоторым образом облегчить себе жизнь при работе над одной из собственных задач. В связи с этим - не ожидайте, что данный редактор будет обновляться очень часто и вообще будет постоянно в активном развитии. 

Реализованный на сегодняшний момент вариант практически полностью удовлетворяет моим потребностям, хотя, имея перед собой пример, как можно реализовать подобное (например дизайнер диалогов TV от L. David Baldwin) я понимаю, что совершенству нет предела... Но эта программа - только "гаечный ключ" и ничего более. Таким образом - постоянная ее доработка и наращивание функционала не планируется. Хотя и вполне вероятна.

Исходя из сказанного и как я обещал автору портированной библиотеки, указанной выше, я выкладываю исходный код проекта в открытый доступ. Если кто желает использовать данный код, для того чтобы доработать программу, улучшить ее функционал - используйте.

Буду благодарен за упоминание моего скромного вклада, если кто-нибудь будет использовать мой код в своих проектах, а также за любую помощь в написании проекта, документировании программы и локализации на другие языки если найдутся на это желающие.

#### А теперь немного о самом проекте:

 - собран с использованием MS Visual Studio 2019 Community Edition;
 - позволяет использовать локализацию интерфейса не "на лету", но все же. Для этого используйте файл multilang.h и задавайте соответствующую константу при сборке проекта;
 - библиотеку TurboVision ищите по ссылке вверху;
 - проверка под Linux не производилась, изначально проект был разработан с использованием TDM MinGW C++ x64 c++14, но по некоторым причинам перенесен в MS VC, тем не менее должен собираться и в Linux;
 - программа должна запускаться от имени администратора иначе с высокой вероятностью будет виснуть;
 - после запуска программа отображает только "палитру компонентов", помеченную в заголовке "D&D". Все как всегда, зажали компонент левым кликом мыши и тащите куда надо, и там бросайте. Над каким окном бросили туда и попадет, несмотря ни на что. Бросили над "desktop" - отменили операцию;
 - никаких окон по умолчанию не создается, используйте меню;
 - программа позволяет использовать механизм Drag&Drop для компонентов, которые полностью реализованы в дизайнере, т.е. создание, настройка и генерация кода;
 - кроме Drag&Drop в созданном диалоговом окне есть контекстное меню, вызываемое по клику на знаке "=" на левой границе окна;
 - сохранение шаблонов в формате *.DLG использует TStreamableClass. Использовать эти диалоги как ресурсы не стоит, поскольку они сохранены с использованием переопределенных компонентов и стандартными не прочтутся. Это предназначено только для дизайна и ничего другого;
 - вставка TListBox / TMemo через контекстное меню диалога НЕ приведет к генерации кода для них и при сохранении в *.DLG при дальнейшей модификации проекта этот ресурс с высокой степенью вероятности станет не загружаемым;
 - и да, программа позволяет редактировать одновременно несколько диалогов;
 - учитывая предыдущий пункт - Copy/Paste между диалоговыми окнами НЕ сделано, не обольщайтесь;
 - в переопределенных компонентах используются строки со стандартной, а не динамической длиной в 255 символов. При этом, при сохранении ресурсов последние становятся заметно больше чем в оригинальной библиотеке. Это сделано просто для упрощения работы загрузки/выгрузки и никак не повлияет на те ресурсы, которые будут генерироваться самой библиотекой.

#### Кратко по редактированию:

- Ctrl+N - создать новый диалог (можно несколько одновременно);
- компонент становится выделенным, когда по нему кликнут (красный цвет);
- перемещение компонента по форме - кликнув и зажав левую клавишу мыши;
- изменение размеров - кликнув и зажав правую кнопку мыши;
- двойной клик на компоненте - вызов его настроек
- Ctrl+Del - удаляет выделенный красным компонент (есть плавающая ошибка, при которой крайне редко удаляются не только красный компонент, но и несколько других, пытаюсь найти, замечено только при удалении строки ввода);
- двойной клик по пустому месту в диалоге - вызов свойств самого диалога.

Самое главное: Alt+X - мгновенно закрывает программу, даже если вы не сохранили измененные диалоги - никаких вопросов задано не будет. Да, это неправильно, я знаю. Пока руки не дошли :)

Все остальное - смотрите на указанные в меню короткие клавиши. 

#### Планы, которые могут быть реализованы, а могут и нет
---
Сразу оговорюсь: то что здесь перечислено - это просто то, чего мне в свое время так не хватало или то, что пришло в голову по результатам собственной тестовой эксплуатации. Но учитывая, что данный проект - просто хобби, помогающее основному направлению деятельности - **ждать, что будет реализовано написанное не стоит**. Можете присоединиться и дописать сами. Как уже говорил - буду рад помощи.

- [ ] добавление редактора свойств или хотя бы его отображение для удобства;
- [ ] добавление TListBox / TMemo в "палитру" компонентов;
- [ ] реализация дополнительных компонентов как отдельной расширяемой библиотеки;
- [ ] переделка базовых компонентов с "выравниванием" API для нормального доступа к функциям и полям, имеющим стандартизированные имена и упорядоченные модификаторы доступа, а не как бог на душу положил в случае стандартной библиотеки;
- [ ] Copy/Paste между редактируемыми окнами;
- [ ] дизайнер меню;
- [ ] дизайнер цветовых схем для использования различными компонентами, поскольку реализацию палитр сделанную в базовой версии считаю убогой и неудобной (могу ошибаться);


---
#### Последние изменения
---
###### 28.01.2022
- [x] Исправлено сохранение в ресурсах при добавлении TCheckBoxes / TRadioButton;
- [x] Контекстное меню редактируемого диалога, вызываемое по правому клику мышки на пустом месте диалога;
- [x] Вставить TMemo можно через контекствное меню диалога, код генерируется (свойства пока что не редактируются);
- [x] Вставить TListBox можно через контекствное меню диалога, код генерируется (свойства пока что не редактируются);
- [x] При использовании выпадающего меню диалога вставка компонентов производится в точку клика правой кнопкой мыши;
- [x] Исправлено действие сохранения диалога, при закрытии через кнопку на окне;
- [x] Изменен состав меню диалога, вызываемого по нажатию на "=";
=======
Все остальное - смотрите на указанные в меню короткие клавиши. 

