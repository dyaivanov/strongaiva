<h1>Программный модуль анализа видеоизображений для гибридного принятия решений в рамках интерактивной симбиотической работы искусственного интеллекта и лица принимающего решения</h1>

Компонент <b>ПО для гибридного принятия решений на базе взаимодействия ИИ и ЛПР на основе моделей профессионального поведения и когнитивных процессов ЛПР в трудноформализуемых задачах с высокой неопределенностью в части повышения качества взаимодействия ИИ и ЛПР в рамках интерактивной совместной («симбиотической») работы сторон (ИИ и ЛПР)</b> предназначен для применения в системах поддержки принятия гибридного принятия решений на базе взаимодействия ИИ и ЛПР на основе моделей профессионального поведения и когнитивных процессов ЛПР в трудноформализуемых задачах с высокой неопределенностью в части повышения качества взаимодействия ИИ и ЛПР в рамках интерактивной совместной («симбиотической») работы сторон (ИИ и ЛПР).   
Компонент разработан на языке С++ с использованием библиотек OpenCV 4.5, OpenPose 1.7, и размещен в репозитории по адресу https://github.com/dyaivanov/strongaiva Для его использования необходим компилятор Qt creator.

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

<h1>Модульные и интеграционные тесты и практические задачи</h1>
Для демонстрации работы необходимо установить открытые библиотеки компьютерного зрения OpenCV 4.5 и OpenPose 1.7. Далее необходимо собрать комплексный проект тестов и задач (https://github.com/dyaivanov/strongaiva/StrongAIVideoAnalysis.pro) программных модулей компонента анализа видеопоследовательностей с использованием Qt Creator (4.12.3, основан на Qt 5.11.0). При успешной сборке должны появится исполняемые файлы в директории .../strongaiva/releases в соответствующих поддиректориях по названию тестов. Далее необходимо произвести запуск автоматической проверки всех тестов, проверка показывает, что ошибок нет, успешное выполнение всех тестов показано на рисунке ниже.

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

<h1>Контрольные примеры</h1>
Модульные и интеграционные тесты составлены для демонстрации всех основных возможностей программной библиотеки сильного ИИ и являются контрольными примерами. На вход примеров отправляются данные (изображения) содержащиеся в директории https://github.com/dyaivanov/strongaiva/inputdata/. Далее рассмотрены выходные значения – входные изображения с наложенной цветографической информацией о выполнении контрольных примеров.

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

