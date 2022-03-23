

# ORCA: SignalReconstruction
The project contains the code for the signal reconstruction at Scale project. This is a project in collaboration with AT&T and UTA on developing highly scalable communication network traffic flow matrix computation.

This project has received several recognitions and awards, including *Communications of the ACM's Research Highlight 2021, VLDB Journal Special Issue on Best of VLDB, ACM SIGMOD Research Highlight Award 2020, and pVLDB Reproducibility Award*.

## Abstract
Signal reconstruction problem (SRP) is an important optimization problem where the objective is to identify a solution to an underdetermined system of linear equations that is closest to a given prior. It has a substantial number of applications in diverse areas, such as network traffic engineering, medical image reconstruction, acoustics, astronomy, and many more. Unfortunately, most of the common approaches for solving SRP do not scale to large problem sizes. 
We propose a novel and scalable algorithm for solving this critical problem. Specifically, we make four major contributions. First, we propose a dual formulation of the problem and develop the Direct algorithm that is significantly more efficient than the state of the art. Second, we show how adapting database techniques developed for scalable similarity joins provides a substantial speedup over Direct. Third, we describe several practical techniques that allow our algorithm to scale—on a single machine—to settings that are orders of magnitude larger than previously studied. Finally, we use the database techniques of materialization and reuse to extend our result to dynamic settings where the input to the SRP changes. Extensive experiments on realworld and synthetic data confirm the efficiency, effectiveness, and scalability of our proposal.

## Publications to cite:
[1] Abolfazl Asudeh, Azade Nazi, Jees Augustine, Saravanan Thirumuruganathan, Nan Zhang, Gautam Das, Divesh Srivastava. Leveraging similarity joins for signal reconstruction. PVLDB, Vol. 11(10), pages 1276--1288, 2018, VLDB Endowment.

[2] (Journal Version) Abolfazl Asudeh, Azade Nazi, Jees Augustine, Saravanan Thirumuruganathan, Nan Zhang, Gautam Das, Divesh Srivastava. Scalable Algorithms for Signal Reconstruction by Leveraging Similarity Joins. VLDB Journal, Vol. 29, pages 681-707, 2020, Special Issue on best of VLDB'18. 
* the code is the implementation used in this (Journal version) paper. It contains the scalability and dynamic updates features.

[3] (Invited Paper) Abolfazl Asudeh, Azade Nazi, Jees Augustine, Saravanan Thirumuruganathan, Nan Zhang, Gautam Das, Divesh Srivastava. Efficient Signal Reconstruction for a Broad Range of Applications. SIGMOD, 2019, Special Issue on 2018 ACM SIGMOD Research Highlights.

[4] (Invited Paper) Abolfazl Asudeh, Jees Augustine, Saravanan Thirumuruganathan, Azade Nazi, Nan Zhang, Gautam Das, Divesh Srivastava. Scalable Signal Reconstruction for a Broad Range of Applications. Communications of the ACM (CACM) Research Highlight, Vol. 64(2), pages 106–115, 2021, ACM.

[5] (Demo) Jees Augustine, Suraj Suresh Shetiya, undefined , Abolfazl Asudeh, Saravanan Thirumuruganathan, Azade Nazi, Nan Zhang, Gautam Das, Divesh Srivastava. Orca-SR: A Real-Time Traffic Engineering Framework leveraging Similarity Joins. PVLDB, 2020, VLDB Endowment.


## Description

1- The SR folder contains the C++ code for the DIRECT and the approximation algorithms.

2- The Python folder contains the code for generating the inputs to the algorithm.


## Authors

* **[Abolfazl Asudeh](https://github.com/asudeh)**
* **[Jees Augustine](https://jeesaugustine.github.io/)**

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

<p align="center"><img width="20%" src="https://www.cs.uic.edu/~indexlab/imgs/InDeXLab2.gif"></p>
