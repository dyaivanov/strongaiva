<a href="https://github.com/dyaivanov/strongaiva/blob/main/README.ru.md">Russian version</a>
<h1>Video analysis software module for hybrid decision making in the framework of interactive symbiotic work of artificial intelligence and a decision maker</h1>

Component <b>Software for hybrid decision making based on the interaction of AI and decision makers based on models of professional behavior and cognitive processes of decision makers in hard-to-formalizable tasks with high uncertainty in terms of improving the quality of interaction between AI and decision makers in the framework of interactive joint ("symbiotic") work of the parties ( AI and decision makers)</b> is intended for use in hybrid decision support systems based on the interaction of AI and decision makers based on models of professional behavior and cognitive processes of decision makers in hard-to-formalizable tasks with high uncertainty in terms of improving the quality of interaction between AI and decision makers within the interactive joint ("symbiotic") work of the parties (AI and decision makers).
The component was developed in C++ using the libraries OpenCV 4.5, OpenPose 1.7, and placed in this repository. To use it, you need the Qt creator compiler.

<h1>Purpose of the software component</h1>
A software component for hybrid decision-making based on the interaction of AI and decision makers based on models of professional behavior and cognitive processes of decision makers in hard-to-formalizable tasks with high uncertainty in terms of improving the quality of interaction between AI and decision makers in the framework of interactive joint ("symbiotic") work of the parties (AI and decision makers) ) implements the functions of strong AI in terms of interpretable data processing by hybrid and composite AI algorithms that reproduce (simulate) human creative activity in solving non-standard problems of interpreting data, extracting meanings and making decisions under uncertainty, including strong AI algorithms in terms of hybrid decision-making algorithms on the basis of interaction between AI and decision makers based on models of professional behavior and cognitive processes of decision makers in difficult-to-formalizable tasks with high uncertainty in terms of improving the quality of interaction between AI and decision makers in the framework of interactive joint ("symbiotic") work of the parties (AI and LPR).

<h1>Application area</h1> 
The scope of this component is the development of software for decision support systems in the field of monitoring the preservation of professional reliability and professional health by employees, especially at objects of special responsibility. Such systems will allow remotely and without causing discomfort to employees, to monitor the physical and psychological state of the employee, his functional reserve and the adequacy of the level of functioning of the body to workloads.

<h1>Functional conditions of use</h1>
Functional restrictions on applications are related to the angles of input video data received from video cameras.
No more than one person should be in the frame at a time.
The image size of the face area must be at least 150 pixels in both dimensions.

<h1>Technical conditions of application</h1>
<table style="border-collapse: collapse; width: 100%;" border="1">
<tbody>
<tr>
<td style="width: 14.2857%;">Computer type</td>
<td style="width: 13.8365%;" width="91">
<p>Number of CPU x number of cores</p>
</td>
<td style="width: 14.1509%;" width="91">
<p>CPU clock frequency, GHz</p>
</td>
<td style="width: 13.8365%;" width="91">
<p>Number of GPU x number of cores</p>
</td>
<td style="width: 14.1509%;" width="91">
<p>GPU clock frequency, GHz</p>
</td>
<td style="width: 15.4088%;" width="91">
<p>RAM, GB</p>
</td>
<td style="width: 14.1509%;" width="91">
<p>Disk memory, TB</p>
</td>
</tr>
<tr>
<td style="width: 14.2857%;" width="102">
<p>Work station</p>
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
<p>32, video memory at least 8</p>
</td>
<td style="width: 14.1509%;" width="91">
<p>1</p>
</td>
</tr>
</tbody>
</table>

Due to the need to use a high-performance graphics accelerator, to perform unit and integration tests, it is necessary to run projects on a computer that meets the specified technical requirements.

<h1>Unit and integration tests and practical tasks</h1>
To demonstrate the work, you need to install the open computer vision libraries OpenCV 4.5 and OpenPose 1.7. Next, you need to assemble a complex project of tests and tasks (https://github.com/dyaivanov/strongaiva/StrongAIVideoAnalysis.pro) of software modules for the video sequence analysis component using Qt Creator (4.12.3, based on Qt 5.11.0). Upon successful build, the executable files should appear in the .../strongaiva/releases directory in the appropriate subdirectories by the name of the tests. Next, you need to run an automatic check of all tests, the check shows that there are no errors, the successful completion of all tests is shown in the figure below.

![image](https://user-images.githubusercontent.com/121159666/211320376-00fd9015-c1e1-4454-83f7-5b836a6d9f25.png)

<h2>Test №1 (analysis of the human skeleton configuration)</h2>
Demonstration of the operation of the detector of primary signs, in particular, the analysis of the configuration of the human skeleton. During the test, the operator can visually control the reliable detection of primary features, in particular, the analysis of the configuration of the human skeleton. Such as the tilt of the torso, the shoulders are raised, the arms to the chest, the arms raised, the hand is close to the face. The result of the test "Analysis of the configuration of the human skeleton" is shown in the figure below.
![image](https://user-images.githubusercontent.com/121159666/211320670-f9adefd3-8967-4f18-98a8-b83805b80759.png)

<h2>Test №2 (detection of the human face area)</h2>
Demonstration of the detector operation, in particular - detection of the human face area. During the test, the operator can make a visual check of the reliable detection of a person's face, as well as the effect of shielding on the detection of a person's face. The result of the “Human Face Area Detection” test is shown in the figure below.

![image](https://user-images.githubusercontent.com/121159666/211323892-ac978d33-8a87-4066-9045-25f8b9e565a9.png)


<h2>Test №3 (detection of the centers of the pupils of the eyes, determination of the direction of a person's gaze)</h2>
Demonstration of the work of detecting the centers of the pupils of the eyes, determining the direction of a person's gaze. In the process of performing the test, the operator can visually control the reliable detection of primary signs, in particular, the detection of the centers of the pupils of the eyes, the determination of the direction of a person's gaze. The result of the test “Detecting the centers of the pupils of the eyes, determining the direction of a person’s gaze” is shown in the figure below.

![image](https://user-images.githubusercontent.com/121159666/211324013-8440789c-6e2d-4faa-bd4b-dfb3880da193.png)

<h2>Test №4 (analysis of human facial expressions)</h2>
Demonstration of the operation of the detector of primary signs, in particular, the analysis of facial expressions of a person's face. In the process of performing the test, the operator can visually control the reliable detection of primary signs, in particular, the analysis of facial expressions of a person's face. Analyze the detection of mimic signs such as head tilt, head down, head to the left, head to the right, eyebrows raised, palpebral fissure narrowed, look at the camera, look at the floor, look to the left, look to the right, single blink, mouth open. The result of the test "Analysis of human facial expressions" is shown in the figure below.

![image](https://user-images.githubusercontent.com/121159666/211324116-d0fd1703-3ba9-41e5-886a-427d4d83ce03.png)

<h2>Test №5 (working with external peripherals)</h2>
Demonstration of work with external peripheral devices. During the test, the operator can control the actuation of the relay controlling the load, if the COM port adapter is not connected, the test will not be passed. The result of the test “Working with external peripherals” is shown in the figure below.

![image](https://user-images.githubusercontent.com/121159666/211324289-3212a933-95d7-48f4-8e4b-c88367a56f1d.png)

<h2>Test №6 (detection of problem areas of interaction between an individual and DSS)</h2>
Demonstration of the detection of problem areas of interaction between an individual and the DSS. During the test, the operator can visually control the signs of psycho-emotional states (such as anger, fear and great excitement) on the test dump of the decision maker's state. The result of the test “Detection of problem areas of interaction between an individual and DSS” is shown in the figure below.

![image](https://user-images.githubusercontent.com/121159666/211324420-f52e7f87-4b8d-4233-b6f3-35fc9ff79f51.png)

<h1>Test cases</h1>
Unit and integration tests are designed to demonstrate all the main features of the strong AI software library and are test cases. The data (images) contained in the directory https://github.com/dyaivanov/strongaiva/inputdata/ is sent to the input of the examples. Next, output values are considered - input images with superimposed colorographic information about the execution of test cases.

<h2>Test №1 (analysis of the human skeleton configuration)</h2>
Demonstration of the operation of the detector of primary signs, in particular, the analysis of the configuration of the human skeleton. During the test, the operator can visually control the reliable detection of primary features, in particular, the analysis of the configuration of the human skeleton. Such as the tilt of the torso, the shoulders are raised, the arms to the chest, the arms raised, the hand is close to the face. The result of the test "Analysis of the configuration of the human skeleton" is shown in the figure

![image](https://user-images.githubusercontent.com/121159666/211324553-a5301e33-0fae-4453-9c79-80ecfd931346.png)

<h2>Test №2 (detection of the human face area)</h2>
Demonstration of the detector operation, in particular - detection of the human face area. During the test, the operator can make a visual check of the reliable detection of a person's face, as well as the effect of shielding on the detection of a person's face. The result of the test “Detection of the human face area” is shown in the figure

![image](https://user-images.githubusercontent.com/121159666/211324820-1f7393e3-e7ff-41af-a3b3-d13ddee3f582.png)

<h2>Test №3 (detection of the centers of the pupils of the eyes, determination of the direction of a person's gaze)</h2>
Demonstration of the work of detecting the centers of the pupils of the eyes, determining the direction of a person's gaze. In the process of performing the test, the operator can visually control the reliable detection of primary signs, in particular, the detection of the centers of the pupils of the eyes, the determination of the direction of a person's gaze. The result of the test “Detection of the centers of the pupils of the eyes, determination of the direction of a person’s gaze” is shown in the figure

![image](https://user-images.githubusercontent.com/121159666/211325198-ae341236-ca06-44a3-8298-8c17914ed5ab.png)

<h2>Test №4 (analysis of human facial expressions)</h2>
Demonstration of the operation of the detector of primary signs, in particular, the analysis of facial expressions of a person's face. In the process of performing the test, the operator can visually control the reliable detection of primary signs, in particular, the analysis of facial expressions of a person's face. Analyze the detection of mimic signs such as head tilt, head down, head to the left, head to the right, eyebrows raised, palpebral fissure narrowed, look at the camera, look at the floor, look to the left, look to the right, single blink, mouth open. The result of the test “Analysis of human facial expressions” is shown in the figure

![image](https://user-images.githubusercontent.com/121159666/211325280-2edd7866-0dc7-4487-8d73-dc57f6faf60c.png)

<h2>Test №5 (working with external peripherals)</h2>
Demonstration of work with external peripheral devices. During the test, the operator can control the actuation of the relay controlling the load, if the COM port adapter is not connected, the test will not be passed.

<h2>Test №6 (detection of problem areas of interaction between an individual and DSS)</h2>
Demonstration of the detection of problem areas of interaction between an individual and the DSS. During the test, the operator can visually control the signs of psycho-emotional states (such as anger, fear and great excitement) on the test dump of the decision maker's state. The result of the test “Detection of problem areas of interaction between an individual and DSS” is shown in the figure

![image](https://user-images.githubusercontent.com/121159666/211325402-9469fdf0-58f1-45ee-b090-282ba25f8819.png)
