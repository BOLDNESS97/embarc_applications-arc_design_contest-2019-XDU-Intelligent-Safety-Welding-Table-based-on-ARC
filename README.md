# Intelligent Safety Welding Table based on ARC
The project is an intelligent safety welding platform based on Synopsys ARC EM processor. When the laboratory personnel are operating the welding table, the instrument works normally. Judging by human infrared sensor, when the operator leaves, the voice module reminds to close the welding platform. If the soldering table is not closed after the operator has been away for a period of time, the power is automatically cut off through the relay module. This project also includes flame sensor, smoke sensor, and GSM module. When the flame sensor and the smoke sensor sense a certain amount of smoke and fire light in the laboratory, the processor immediately determines that there may be a fire, giving priority to the welding table through the relay There are hidden dangers in voice broadcasting through power outage and voice module, and text messages are sent to laboratory administrators through GSM module to inform them to check the hidden dangers in time.
* [Introduction](#introduction)
	* [Project context](#project-context)
	* [System Architecture](#system-architecture)
        * [Function](#function)
* [Hardware and Software Setup](#hardware-and-software-setup)
	* [Required Hardware](#required-hardware)
	* [Required Software](#required-software)
	* [Hardware Connection](#hardware-connection)
* [User Manual](#user-manual)
	* [Before Running This Application](#before-running-this-application)
	* [Run This Application](#run-this-application)
	* [DemoVideo](#demovideo)
## Introduction
### Project context
With the progress and development of science and technology, more and more colleges and universities are committed to cultivating college students' scientific literacy and strengthening practical skills and entrepreneurial ability. The establishment of innovation laboratory for college students has become the main place and platform for college students to impart knowledge, develop intelligence, cultivate college students' scientific quality and skills, cultivate college students' innovative spirit, entrepreneurial consciousness, innovative entrepreneurial ability and so on. It has an irreplaceable and unique role, stimulates students' innovative thinking and innovative consciousness, but also constructs innovative educational culture, and comprehensively improves students' innovative experimental ability. However, with the increase of laboratory students and the difficulty of management, it is also gradually becoming more and more difficult. There are some hidden dangers, such as irregular use of sockets and sockets, electric soldering iron, hot air gun, and other laboratory instruments and equipment have not been turned off from time to time, and it is easy to cause fire accidents.
![0](https://github.com/pfli07/Intelligent-protection-system-for-forgotten
