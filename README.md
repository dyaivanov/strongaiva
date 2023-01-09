Компонент ПО для гибридного принятия решений на базе взаимодействия ИИ и ЛПР на основе моделей профессионального поведения и когнитивных процессов ЛПР в трудноформализуемых задачах с высокой неопределенностью в части повышения качества взаимодействия ИИ и ЛПР в рамках интерактивной совместной («симбиотической») работы сторон (ИИ и ЛПР)предназначен для применения в системах поддержки принятия гибридного принятия решений на базе взаимодействия ИИ и ЛПР на основе моделей профессионального поведения и когнитивных процессов ЛПР в трудноформализуемых задачах с высокой неопределенностью в части повышения качества взаимодействия ИИ и ЛПР в рамках интерактивной совместной («симбиотической») работы сторон (ИИ и ЛПР).   
Компонент разработан на языке С++ с использованием библиотек OpenCV 4.5, OpenPose 1.7, и размещен в репозитории по адресу https://github.com/dyaivanov/strongaiva Для его использования необходим компилятор Qt creator.

Назначение программного компонента
Компонент ПО для гибридного принятия решений на базе взаимодействия ИИ и ЛПР на основе моделей профессионального поведения и когнитивных процессов ЛПР в трудноформализуемых задачах с высокой неопределенностью в части повышения качества взаимодействия ИИ и ЛПР в рамках интерактивной совместной («симбиотической») работы сторон (ИИ и ЛПР) реализует функции сильного  ИИ в части интерпретируемой обработки данных алгоритмами гибридного и композитного ИИ, воспроизводящими (имитирующими) творческую деятельность человека при решении нестандартных задач интерпретации данных, извлечения смыслов и принятия решений в условиях неопределенности, включая алгоритмы сильного ИИ в части алгоритмов гибридного принятия решений на базе взаимодействия ИИ и ЛПР на основе моделей профессионального поведения и когнитивных процессов ЛПР в трудноформализуемых задачах с высокой неопределенностью в части повышения качества взаимодействия ИИ и ЛПР в рамках интерактивной совместной («симбиотической») работы сторон (ИИ и ЛПР).

Область применения 
Областью применения данного компонента является разработка программного обеспечения систем поддержки принятия решений в сфере контроля за сохранением работниками профессиональной надежности и профессионального здоровья, особенно на объектах особой ответственности. Такие системы позволят дистанционно и без причинения дискомфорта для работников, осуществлять контроль физического и психологического состояния сотрудника, его функционального резерва и адекватности уровня функционирования организма рабочим нагрузкам.

Функциональные условия применения
Функциональные ограничения на применения связаны с ракурсами входных видеоданных, получаемыми от видеокамер. 
В кадр одновременно должно попадать не более одного человека. 
Размер изображения области лица должен быть не менее 150 пикселей по обоим измерениям.

Технческие условия применения
Тип компьютера	Кол-во CPU х кол-во ядер	Тактовая частота CPU, ГГц	Кол-во GPU x кол-во ядер	Тактовая частота GPU, ГГц	Оперативная память, Гб	Дисковая память, Тб
Рабочая станция	1х8	2,8	1 х 4352	1,6	32, объем видеопамяти не менее 8	1

В связи с необходимостью применения высокопроизводительного графического ускорителя, для выполнения модульных и интеграционных тестов необходимо запускать проекты на компьютере, удовлетворяющем выдвинутым техническим требованиям.

Модульные и интеграционные тесты и практические задачи
Для демонстрации работы необходимо установить открытые библиотеки компьютерного зрения OpenCV 4.5 и OpenPose 1.7. Далее необходимо собрать комплексный проект тестов и задач (StrongAIVideoAnalysis\StrongAIVideoAnalysis.pro) программных модулей компонента анализа видеопоследовательностей с использованием Qt Creator (4.12.3, основан на Qt 5.11.0). При успешной сборке должны появится исполняемые файлы в директории StrongAIVideoAnalysis\releases\ в соответствующих поддиректориях по названию тестов. Далее необходимо произвести запуск автоматической проверки всех тестов, проверка показывает, что ошибок нет, успешное выполнение всех тестов показано на рисунке ниже.

![image](https://user-images.githubusercontent.com/121159666/211320376-00fd9015-c1e1-4454-83f7-5b836a6d9f25.png)

Тест №1 (анализ конфигурации скелета человека)
Демонстрация работы детектора первичных признаков, в частности, анализ конфигурации скелета человека. В процессе выполнения теста оператор может произвести визуальный контроль достоверного детектирования первичных признаков, в частности, анализа конфигурации скелета человека. Таких как наклон туловища, плечи подняты, руки к груди, поднятые руки, рука приближена к лицу. Результат выполнения теста “Анализ конфигурации скелета человека” показан на рисунке нже.

![image](https://user-images.githubusercontent.com/121159666/211320670-f9adefd3-8967-4f18-98a8-b83805b80759.png)

Тест №2 (детектирование области лица человека)
Демонстрация работы детектора, в частности -	детектирование области лица человека. В процессе выполнения теста оператор может произвести визуальный контроль достоверного детектирования лица человека, а также влияние экранирования на детектирование лица человека. Результат выполнения теста “Детектирование области лица человека” показан на рисунке ниже.


