[![SAI](https://github.com/ITMO-NSS-team/open-source-ops/blob/master/badges/SAI_badge_flat.svg)](https://sai.itmo.ru/)
[![ITMO](https://github.com/ITMO-NSS-team/open-source-ops/blob/master/badges/ITMO_badge_flat_rus.svg)](https://en.itmo.ru/en/)

[![Eng](https://img.shields.io/badge/lang-en-red.svg)](/README.en.md)
[![Mirror](https://camo.githubusercontent.com/9bd7b8c5b418f1364e72110a83629772729b29e8f3393b6c86bff237a6b784f6/68747470733a2f2f62616467656e2e6e65742f62616467652f6769746c61622f6d6972726f722f6f72616e67653f69636f6e3d6769746c6162)](https://gitlab.actcognitive.org/itmo-sai-code/strongaiva)

<h1>Программный модуль анализа видеоизображений для гибридного принятия решений в рамках интерактивной симбиотической работы искусственного интеллекта и лица принимающего решения</h1>

Компонент <b>ПО для гибридного принятия решений на базе взаимодействия ИИ и ЛПР на основе моделей профессионального поведения и когнитивных процессов ЛПР в трудноформализуемых задачах с высокой неопределенностью в части повышения качества взаимодействия ИИ и ЛПР в рамках интерактивной совместной («симбиотической») работы сторон (ИИ и ЛПР)</b> предназначен для применения в системах поддержки принятия гибридного принятия решений на базе взаимодействия ИИ и ЛПР на основе моделей профессионального поведения и когнитивных процессов ЛПР в трудноформализуемых задачах с высокой неопределенностью в части повышения качества взаимодействия ИИ и ЛПР в рамках интерактивной совместной («симбиотической») работы сторон (ИИ и ЛПР).   
Компонент разработан на языке С++ с использованием библиотек OpenCV 4.5, OpenPose 1.7, и размещен в данном репозитории. Для его использования необходим компилятор Qt creator.

<h1>Назначение программного компонента</h1>
Компонент ПО для гибридного принятия решений на базе взаимодействия ИИ и ЛПР на основе моделей профессионального поведения и когнитивных процессов ЛПР в трудноформализуемых задачах с высокой неопределенностью в части повышения качества взаимодействия ИИ и ЛПР в рамках интерактивной совместной («симбиотической») работы сторон (ИИ и ЛПР) реализует функции сильного  ИИ в части интерпретируемой обработки данных алгоритмами гибридного и композитного ИИ, воспроизводящими (имитирующими) творческую деятельность человека при решении нестандартных задач интерпретации данных, извлечения смыслов и принятия решений в условиях неопределенности, включая алгоритмы сильного ИИ в части алгоритмов гибридного принятия решений на базе взаимодействия ИИ и ЛПР на основе моделей профессионального поведения и когнитивных процессов ЛПР в трудноформализуемых задачах с высокой неопределенностью в части повышения качества взаимодействия ИИ и ЛПР в рамках интерактивной совместной («симбиотической») работы сторон (ИИ и ЛПР).

<h1>Область применения</h1> 
Областью применения данного компонента является разработка программного обеспечения систем поддержки принятия решений в сфере контроля за сохранением работниками профессиональной надежности и профессионального здоровья, особенно на объектах особой ответственности. Такие системы позволят дистанционно и без причинения дискомфорта для работников, осуществлять контроль физического и психологического состояния сотрудника, его функционального резерва и адекватности уровня функционирования организма рабочим нагрузкам.

<h1>Функциональные условия применения</h1>
Функциональные ограничения на применения связаны с ракурсами входных видеоданных, получаемыми от видеокамер. 
В кадр одновременно должно попадать не более одного человека. 
Размер изображения области лица должен быть не менее 150 пикселей по обоим измерениям.

<h1>Технческие условия применения</h1>
<table style="border-collapse: collapse; width: 100%;" border="1">
<tbody>
<tr>
<td style="width: 14.2857%;">Тип компьютера</td>
<td style="width: 13.8365%;" width="91">
<p>Кол-во CPU х кол-во ядер</p>
</td>
<td style="width: 14.1509%;" width="91">
<p>Тактовая частота CPU, ГГц</p>
</td>
<td style="width: 13.8365%;" width="91">
<p>Кол-во GPU x кол-во ядер</p>
</td>
<td style="width: 14.1509%;" width="91">
<p>Тактовая частота GPU, ГГц</p>
</td>
<td style="width: 15.4088%;" width="91">
<p>Оперативная память, Гб</p>
</td>
<td style="width: 14.1509%;" width="91">
<p>Дисковая память, Тб</p>
</td>
</tr>
<tr>
<td style="width: 14.2857%;" width="102">
<p>Рабочая станция</p>
</td>
<td style="width: 13.8365%;" width="91">
<p>1х8</p>
</td>
<td style="width: 14.1509%;" width="91">
<p>2,8</p>
</td>
<td style="width: 13.8365%;" width="91">
<p>1 х 4352</p>
</td>
<td style="width: 14.1509%;" width="91">
<p>1,6</p>
</td>
<td style="width: 15.4088%;" width="91">
<p>32, объем видеопамяти не менее 8</p>
</td>
<td style="width: 14.1509%;" width="91">
<p>1</p>
</td>
</tr>
</tbody>
</table>

В связи с необходимостью применения высокопроизводительного графического ускорителя, для выполнения модульных и интеграционных тестов необходимо запускать проекты на компьютере, удовлетворяющем выдвинутым техническим требованиям.

<h1 id="tests">Модульные и интеграционные тесты и практические задачи</h1>
Для демонстрации работы необходимо установить открытые библиотеки компьютерного зрения OpenCV 4.5 и OpenPose 1.7. Далее необходимо собрать комплексный проект тестов и задач (../strongaiva/StrongAIVideoAnalysis.pro) программных модулей компонента анализа видеопоследовательностей с использованием Qt Creator (4.12.3, основан на Qt 5.11.0). При успешной сборке должны появится исполняемые файлы в директории .../strongaiva/releases в соответствующих поддиректориях по названию тестов. Далее необходимо произвести запуск автоматической проверки всех тестов, проверка показывает, что ошибок нет, успешное выполнение всех тестов показано на рисунке ниже.

![image](https://user-images.githubusercontent.com/121159666/211320376-00fd9015-c1e1-4454-83f7-5b836a6d9f25.png)

<h2>Тест №1 (анализ конфигурации скелета человека)</h2>
Демонстрация работы детектора первичных признаков, в частности, анализ конфигурации скелета человека. В процессе выполнения теста оператор может произвести визуальный контроль достоверного детектирования первичных признаков, в частности, анализа конфигурации скелета человека. Таких как наклон туловища, плечи подняты, руки к груди, поднятые руки, рука приближена к лицу. Результат выполнения теста “Анализ конфигурации скелета человека” показан на рисунке нже.

![image](https://user-images.githubusercontent.com/121159666/211320670-f9adefd3-8967-4f18-98a8-b83805b80759.png)

<h2>Тест №2 (детектирование области лица человека)</h2>
Демонстрация работы детектора, в частности -	детектирование области лица человека. В процессе выполнения теста оператор может произвести визуальный контроль достоверного детектирования лица человека, а также влияние экранирования на детектирование лица человека. Результат выполнения теста “Детектирование области лица человека” показан на рисунке ниже.

![image](https://user-images.githubusercontent.com/121159666/211323892-ac978d33-8a87-4066-9045-25f8b9e565a9.png)


<h2>Тест №3 (детектирование центров зрачков глаз, определение направления взгляда человека)</h2>
Демонстрация работы детектирования центров зрачков глаз, определение направления взгляда человека. В процессе выполнения теста оператор может произвести визуальный контроль достоверного детектирования первичных признаков, в частности, детектирование центров зрачков глаз, определение направления взгляда человека. Результат выполнения теста “Детектирование центров зрачков глаз, определение направления взгляда человека” показан на рисунке ниже.

![image](https://user-images.githubusercontent.com/121159666/211324013-8440789c-6e2d-4faa-bd4b-dfb3880da193.png)

<h2>Тест №4 (анализ мимики лица человека)</h2>
Демонстрация работы детектора первичных признаков, в частности, анализ мимики лица человека. В процессе выполнения теста оператор может произвести визуальный контроль достоверного детектирования первичных признаков, в частности, анализ мимики лица человека. Произвести анализ детектирования мимических признаков таких как наклон головы, голова опущена, голова влево, голова вправо, брови приподняты, сужена глазная щель, взгляд в камеру, взгляд в пол, взгляд влево, взгляд вправо, однократное моргание, рот раскрыт. Результат выполнения теста “Анализ мимики лица человека” показан на рисунке ниже.

![image](https://user-images.githubusercontent.com/121159666/211324116-d0fd1703-3ba9-41e5-886a-427d4d83ce03.png)

<h2>Тест №5 (работа с внешними периферийными устройствами)</h2>
Демонстрация работы с внешними периферийными устройствами. В процессе выполнения теста оператор может произвести контроль сработки реле управляющего нагрузкой, если адаптер COM-порта не подключен тест не будет пройден. Результат выполнения теста “Работа с внешними периферийными устройствами” показан на рисунке ниже.

![image](https://user-images.githubusercontent.com/121159666/211324289-3212a933-95d7-48f4-8e4b-c88367a56f1d.png)

<h2>Тест №6 (детекция проблемных областей взаимодействия индивида и СППР)</h2>
Демонстрация работы детекции проблемных областей взаимодействия индивида и СППР. В процессе выполнения теста оператор может произвести визуальный контроль признаков психоэмоциональных состояний (таких как гнев, страх и сильное волнение) на тестовом дампе состояния ЛПР. Результат выполнения теста “Детекция проблемных областей взаимодействия индивида и СППР” показан на рисунке ниже.

![image](https://user-images.githubusercontent.com/121159666/211324420-f52e7f87-4b8d-4233-b6f3-35fc9ff79f51.png)

<h1 id="test_cases">Контрольные примеры</h1>
Модульные и интеграционные тесты составлены для демонстрации всех основных возможностей программной библиотеки сильного ИИ и являются контрольными примерами. На вход примеров отправляются данные (изображения) содержащиеся в директории ../strongaiva/inputdata/. Далее рассмотрены выходные значения – входные изображения с наложенной цветографической информацией о выполнении контрольных примеров.

<h2>Тест №1 (анализ конфигурации скелета человека)</h2>
Демонстрация работы детектора первичных признаков, в частности, анализ конфигурации скелета человека. В процессе выполнения теста оператор может произвести визуальный контроль достоверного детектирования первичных признаков, в частности, анализа конфигурации скелета человека. Таких как наклон туловища, плечи подняты, руки к груди, поднятые руки, рука приближена к лицу. Результат выполнения теста “Анализ конфигурации скелета человека” показан на рисунке

![image](https://user-images.githubusercontent.com/121159666/211324553-a5301e33-0fae-4453-9c79-80ecfd931346.png)

<h2>Тест №2 (детектирование области лица человека)</h2>
Демонстрация работы детектора, в частности -	детектирование области лица человека. В процессе выполнения теста оператор может произвести визуальный контроль достоверного детектирования лица человека, а также влияние экранирования на детектирование лица человека. Результат выполнения теста “Детектирование области лица человека” показан на рисунке

![image](https://user-images.githubusercontent.com/121159666/211324820-1f7393e3-e7ff-41af-a3b3-d13ddee3f582.png)

<h2>Тест №3 (детектирование центров зрачков глаз, определение направления взгляда человека)</h2>
Демонстрация работы детектирования центров зрачков глаз, определение направления взгляда человека. В процессе выполнения теста оператор может произвести визуальный контроль достоверного детектирования первичных признаков, в частности, детектирование центров зрачков глаз, определение направления взгляда человека. Результат выполнения теста “Детектирование центров зрачков глаз, определение направления взгляда человека” показан на рисунке 

![image](https://user-images.githubusercontent.com/121159666/211325198-ae341236-ca06-44a3-8298-8c17914ed5ab.png)

<h2>Тест №4 (анализ мимики лица человека)</h2>
Демонстрация работы детектора первичных признаков, в частности, анализ мимики лица человека. В процессе выполнения теста оператор может произвести визуальный контроль достоверного детектирования первичных признаков, в частности, анализ мимики лица человека. Произвести анализ детектирования мимических признаков таких как наклон головы, голова опущена, голова влево, голова вправо, брови приподняты, сужена глазная щель, взгляд в камеру, взгляд в пол, взгляд влево, взгляд вправо, однократное моргание, рот раскрыт. Результат выполнения теста “Анализ мимики лица человека” показан на рисунке

![image](https://user-images.githubusercontent.com/121159666/211325280-2edd7866-0dc7-4487-8d73-dc57f6faf60c.png)

<h2>Тест №5 (работа с внешними периферийными устройствами)</h2>
Демонстрация работы с внешними периферийными устройствами. В процессе выполнения теста оператор может произвести контроль сработки реле управляющего нагрузкой, если адаптер COM-порта не подключен тест не будет пройден.

<h2>Тест №6 (детекция проблемных областей взаимодействия индивида и СППР)</h2>
Демонстрация работы детекции проблемных областей взаимодействия индивида и СППР. В процессе выполнения теста оператор может произвести визуальный контроль признаков психоэмоциональных состояний (таких как гнев, страх и сильное волнение) на тестовом дампе состояния ЛПР. Результат выполнения теста “Детекция проблемных областей взаимодействия индивида и СППР” показан на рисунке 

![image](https://user-images.githubusercontent.com/121159666/211325402-9469fdf0-58f1-45ee-b090-282ba25f8819.png)

<h1>Классы решаемых задач</h1>
<p>Разработанное программное обеспечение предназначено для решения прикладных задач гибридного принятия решений на базе взаимодействия интеллектуальных систем поддержки принятия решений и других интеллектуальных систем и лиц, принимающих решения на основе моделей профессионального поведения и когнитивных процессов в трудно формализуемых задачах с высокой неопределенностью.</p>
<p>Данный компонент может использоваться при решении следующих классов задач:</p>
<ul>
<li>управление режимами работы промышленного оборудования в соответствии с поведением и состоянием персонала с целью снижения риска производственного травматизма;</li>
<li>предотвращение сбоев и простоев в работе сборочных и конвейерных линий, вызванных снижением времени реакции сотрудников;</li>
<li>предотвращение порчи и выхода из строя оборудования, в том числе дистанционно управляемых аппаратов, за счет их перевода в самосберегающий режим (Save Mode) на основе оценки психоэмоционального состояния оператора.</li>
</ul>

<h2 id="examples">Примеры решаемых задач</h2>
<ul>
<li>мониторинг и контроль эмоциональных состояний оператора при работе с СППР и операторов при работе с промышленным оборудованием, станками, пультами управления производственными линиями и другим оборудованием повышенной ответственности.</li>
<li>детекция проблемных областей взаимодействия СППР и оператора беспилотного летательного оператора при проведении промышленно-геодезических и других видов работ.</li>
  </ul>
Мониторинг и контроль эмоциональных состояний ЛПР или операторов оборудования повышенной ответственности необходимы для обеспечения безопасной и непрерывной работы сложных мехатронных комплексов и промышленных производственных линий. 
Детектирование проблемных областей взаимодействия систем поддержки принятия решений и операторов беспилотных летательных аппаратов необходимо для учета скорости реакции и способности оператора к концентрации внимания.

<h2>Мониторинг и контроль эмоциональных состояний ЛПР при работе со станками</h2>

<b>Постановка задачи</b>
<p>Задача контроля эмоционального состояния ЛПР востребована во многих областях промышленности и производства, рассмотрим на примере работы со сверлильным станком. Аналогично решение данной задачи может быть применено к другим станкам, например, токарному и фрезерному в том числе с ЧПУ управлением.</p>
<b>Исходные данные</b>
<p>В качестве исходных данных выступает видеоинформация, получаемая с камеры ноутбука/внешняя USB-камера, отслеживающая состояние ЛПР. Обратная связь с объектом управления (сверлильным станком) осуществляется через интерфейс виртуального COM-порта ПК, и реле управляющего мощной нагрузкой. В случае если система видеоанализа фиксирует эмоциональные состояния недопустимые при работе с механическим обрабатывающим станком, производится аварийная остановка станка.</p>
<b>Решение задачи</b>
<p>Для решения задачи применяются некоторые фрагменты примеров библиотеки алгоритмов сильного ИИ. В частности:
  <ul>  
    <li>пример решения задачи анализ конфигурации скелета человека;</li>
    <li>пример детектирования области лица человека;</li>
    <li>пример детектирования центров зрачков глаз и направления взгляда;</li>
    <li>пример анализа мимики лица человека;</li>
    <li>пример управления периферийными устройствами;</li>
    <li>пример решения задачи детекции проблемных областей взаимодействия индивида и СППР.</li>
   </ul>
Данные примеры подробно описаны в п.5.2. Проект задачи мониторинга и контроля эмоциональных состояний ЛПР при работе со станками находится ../strongaiva/TaskMachineControlAI/TaskMachineControlAI.pro 
</p>

<b>Результаты и их содержательная интерпретация</b>
<p>Результаты решения задачи мониторинга и контроля эмоциональных состояний ЛПР при работе со станками были продемонстрированы с использованием малогабаритного сверлильного станка. Оператор станка моделировал ситуацию недопустимого поведения при работе с данным станком, в результате на основе анализа его эмоционального состояния производилось аварийная остановка станка.</p>
На рисунках ниже показаны фотографии при выполнении примера решения задачи по мониторингу и контролью эмоциональных состояний оператора при работе с промышленным оборудованием на примере сверлильного станка.

![image](https://user-images.githubusercontent.com/121159666/212894261-df0a2536-ceb3-447d-a070-7caac73a1a6c.png)

![image](https://user-images.githubusercontent.com/121159666/212894298-d09bcad6-aa45-41a5-b916-df5fc95fd37a.png)

<h2>Детекция проблемных областей взаимодействия СППР и оператора беспилотного летательного аппарата</h2>

<b>Постановка задачи</b>
<p>В связи с применением большого количества беспилотных летательных аппаратов в современном мире для широкого спектра задач задача детекции проблемных областей взаимодействия СППР и оператора беспилотного летательного оператора для промышленно-геодезических работ является наиболее востребованной. Аналогично решение данной задачи может быть применено к другим беспилотным летательным и наземного базирования аппаратам.</p>

<b>Исходные данные</b>
<p>В качестве исходных данных выступает видеоинформация, получаемая с камеры ноутбука/внешняя USB-камера, отслеживающая состояние ЛПР. Обратная связь с объектом управления беспилотного летательного аппарата осуществляется через интерфейс виртуального COM-порта ПК, и протокола управления пульта беспилотного летательного аппарата. В случае если система видеоанализа фиксирует эмоциональные состояния ЛПР недопустимые при работе с пультом беспилотного летательного аппарата, производится отправка команды возвращения в точку старта.</p>

<b>Решение задачи</b>
<p>Для решения задачи детекции проблемных областей взаимодействия СППР и оператора беспилотного летательного оператора для промышленно-геодезических работ применяются некоторые фрагменты примеров библиотеки алгоритмов сильного ИИ. В частности:</p>
<ul>
  <li>пример решения задачи анализ конфигурации скелета человека;</li>
  <li>пример детектирования области лица человека;</li>
  <li>пример детектирования центров зрачков глаз и направления взгляда;</li>
  <li>пример анализа мимики лица человека;</li>
  <li>пример управления периферийными устройствами;</li>
  <li>пример решения задачи детекции проблемных областей взаимодействия индивида и СППР.</li>
</ul>
Проект задачи детекции проблемных областей взаимодействия СППР и оператора беспилотного летательного оператора для промышленно-геодезических работ находится в директории 
../strongaiva/TaskCopterControlAI/TaskCopterControlAI.pro

<b>Результаты и их содержательная интерпретация</b>
<p>Результаты решения задачи детекции проблемных областей взаимодействия СППР и оператора беспилотного летательного оператора для промышленно-геодезических работ были продемонстрированы с использованием малогабаритного квадрокоптера, оборудованного телевизионной камерой. Оператор беспилотного летательного аппарата моделировал ситуацию недопустимого поведения при работе с данным объектом управления, в результате на основе анализа его эмоционального состояния производилась отправка команды возвращения в точку старта.</p>

На рисунках ниже показаны фотографии при выполнении примера решения задачи детекция проблемных областей взаимодействия СППР и оператора беспилотного летательного оператора на прмере дистанционного управления квадрокоптером.

![image](https://user-images.githubusercontent.com/121159666/212894468-a7978650-a171-42ba-a230-beb9388e1578.png)

![image](https://user-images.githubusercontent.com/121159666/212894509-6e8902cf-be1f-47ab-8451-4b3e7403b099.png)

