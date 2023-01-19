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
To demonstrate the work, you need to install the open computer vision libraries OpenCV 4.5 and OpenPose 1.7. Next, you need to assemble a complex project of tests and tasks (../strongaiva/StrongAIVideoAnalysis.pro) of software modules for the video sequence analysis component using Qt Creator (4.12.3, based on Qt 5.11.0). Upon successful build, the executable files should appear in the .../strongaiva/releases directory in the appropriate subdirectories by the name of the tests. Next, you need to run an automatic check of all tests, the check shows that there are no errors, the successful completion of all tests is shown in the figure below.

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
Unit and integration tests are designed to demonstrate all the main features of the strong AI software library and are test cases. The data (images) contained in the directory ../dyaivanov/strongaiva/inputdata/ is sent to the input of the examples. Next, output values are considered - input images with superimposed colorographic information about the execution of test cases.

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

<h1>Classes of solving problems</h1>
<p>The developed software is designed to solve applied problems of hybrid decision making based on the interaction of intelligent decision support systems and other intelligent systems and decision makers based on models of professional behavior and cognitive processes in difficultly formalized tasks with high uncertainty.</p>
<p>This component can be used to solve the following classes of problems:</p>
<ul>
<li>management of industrial equipment operating modes in accordance with the behavior and condition of personnel in order to reduce the risk of industrial injuries;</li>
<li>prevention of failures and downtime in the work of assembly and conveyor lines caused by a decrease in the reaction time of employees;</li>
<li>prevention of damage and failure of equipment, including remotely controlled vehicles, by switching them to a self-saving mode (Save Mode) based on an assessment of the psycho-emotional state of the operator.</li>
</ul>

<h2 id="examples">Examples of solved problems</h2>
<ul>
<li>monitoring and control of the emotional states of the operator when working with DSS and operators when working with industrial equipment, machine tools, control panels for production lines and other equipment of increased responsibility.</li>
<li>detection of problem areas of interaction between the DSS and the operator of an unmanned aerial operator during industrial geodetic and other types of work.</li>
   </ul>
Monitoring and control of the emotional states of decision makers or operators of equipment of increased responsibility are necessary to ensure the safe and continuous operation of complex mechatronic complexes and industrial production lines.
Detection of problem areas of interaction between decision support systems and operators of unmanned aerial vehicles is necessary to take into account the reaction speed and the operator's ability to concentrate.

<h2>Monitoring and control of decision makers' emotional states when working with machines</h2>

<b>Problem statement</b>
<p>The task of controlling the emotional state of decision makers is in demand in many areas of industry and production, let's consider the example of working with a drilling machine. Similarly, the solution of this problem can be applied to other machines, for example, turning and milling, including those with CNC control.</p>
<b>Initial data</b>
<p>The initial data is the video information received from the laptop camera / external USB camera that monitors the state of the decision maker. Feedback with the control object (drilling machine) is carried out through the interface of the virtual COM port of the PC, and the relay that controls the powerful load. If the video analysis system captures emotional states that are unacceptable when working with a mechanical processing machine, an emergency stop of the machine is performed.</p>
<b>Solution of the problem</b>
<p>Some fragments of examples of the strong AI algorithm library are used to solve the problem. In particular:
   <ul>
     <li>an example of solving the problem of analyzing the configuration of the human skeleton;</li>
     <li>example of human face area detection;</li>
     <li>an example of detecting the centers of the pupils of the eyes and the direction of gaze;</li>
     <li>an example of the analysis of human facial expressions;</li>
     <li>peripheral device control example;</li>
     <li>an example of solving the problem of detecting problem areas of interaction between an individual and a DSS.</li>
    </ul>
These examples are described in detail in paragraph 5.2. The project of the task of monitoring and controlling the emotional states of decision makers when working with machines is located at https://github.com/dyaivanov/strongaiva/TaskMachineControlAI/TaskMachineControlAI.pro
</p>

<b>Results and their meaningful interpretation</b>
<p>The results of solving the problem of monitoring and controlling the emotional states of decision makers when working with machine tools were demonstrated using a small-sized drilling machine. The machine operator simulated a situation of unacceptable behavior when working with this machine, as a result, based on the analysis of his emotional state, an emergency stop of the machine was made.</p>
The figures below show photographs of an example of solving the task of monitoring and controlling the emotional states of an operator when working with industrial equipment using a drilling machine as an example.

![image](https://user-images.githubusercontent.com/121159666/212894261-df0a2536-ceb3-447d-a070-7caac73a1a6c.png)

![image](https://user-images.githubusercontent.com/121159666/212894298-d09bcad6-aa45-41a5-b916-df5fc95fd37a.png)

<h2>Detection of problem areas of interaction between the DSS and the operator of an unmanned aerial vehicle</h2>

<b>Problem statement</b>
<p>In connection with the use of a large number of unmanned aerial vehicles in the modern world for a wide range of tasks, the task of detecting problem areas of interaction between the DSS and the operator of an unmanned aerial vehicle for industrial geodetic work is the most in demand. Similarly, the solution of this problem can be applied to other unmanned aerial and ground-based vehicles.</p>

<b>Initial data</b>
<p>The initial data is the video information received from the laptop camera / external USB camera that monitors the state of the decision maker. Feedback with the control object of the unmanned aerial vehicle is carried out through the interface of the virtual COM port of the PC, and the control protocol of the unmanned aerial vehicle console. If the video analysis system captures the emotional states of the decision maker that are unacceptable when working with the remote control of an unmanned aerial vehicle, a command is sent to return to the starting point.</p>

<b>Solution of the problem</b>
<p>To solve the problem of detecting problem areas of interaction between a DSS and an unmanned aerial vehicle operator for industrial geodetic work, some fragments of examples of a library of strong AI algorithms are used. In particular:</p>
<ul>
   <li>an example of solving the problem of analyzing the configuration of the human skeleton;</li>
   <li>example of human face area detection;</li>
   <li>an example of detecting the centers of the pupils of the eyes and the direction of gaze;</li>
   <li>an example of the analysis of human facial expressions;</li>
   <li>peripheral device control example;</li>
   <li>an example of solving the problem of detecting problem areas of interaction between an individual and a DSS.</li>
</ul>
The project of the task of detecting problem areas of interaction between the DSS and the operator of an unmanned aerial operator for industrial and geodetic works is located in the directory
../strongaiva/TaskCopterControlAI/TaskCopterControlAI.pro

<b>Results and their meaningful interpretation</b>
<p>The results of solving the problem of detecting problem areas of interaction between the DSS and the operator of an unmanned aerial operator for industrial geodetic work were demonstrated using a small-sized quadrocopter equipped with a television camera. The operator of an unmanned aerial vehicle simulated a situation of unacceptable behavior when working with this control object, as a result, based on the analysis of his emotional state, a command was sent to return to the starting point.</p>

The figures below show photographs when executing an example of solving the problem of detecting problem areas of interaction between the DSS and the operator of an unmanned aerial operator on the example of remote control of a quadrocopter.

![image](https://user-images.githubusercontent.com/121159666/212894468-a7978650-a171-42ba-a230-beb9388e1578.png)

![image](https://user-images.githubusercontent.com/121159666/212894509-6e8902cf-be1f-47ab-8451-4b3e7403b099.png)

