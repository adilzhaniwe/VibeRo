# Instruction for VibeRo's Stimulation Strategy

The aim of this project was to generate the haptic illusion of squeezing soft virtual objects. The process of creating the stimulation strategy and validation of results are described here in details. 

Firstly, we have to decide what does a softness of an object mean? What kind of tactile cues we perceive when interacting with soft objects? So, let's begin from the theory of touch and human tactile sensing. 

### 1. Theory 

From the article: 
> Human tactile perception consists of four types of mechanoreceptors, including fast adapting type I (FA-I), fast adapting type II (FA-II), slow adapting type I (SA-I) and slow adapting type II (SA-II), that provide information about physical interactions. SA-I and SA-II detect static forces due to the skin stretch. FA-I and FA-II detect changes at the points of contact, such as vibrations induced by slippage and other types of motions. Interestingly, FA-I and FA-II seem to be responsible for texture discrimination and slip detection. Inspired by this, the state-of-the-art VR controllers leverage voice-coil actuators to provide a more realistic perception of the VE by stimulating FA-I mechanoreceptors.

This mean that when touching a deformable object (soft objects are deformable) 
Squeezing a soft object filled with granular particles (e.g. coffee grains, salt and sugar) induces sound that is referred to us as “squeeze induced vibrations”. Similar vibrations can be generated using the described above haptic system. Then the tactile stimulus is a lateral oscillation of the voice coil actuator. The frequency of the oscillation is modulated by the rate of change of the applied force so that the desired lateral displacement of the coil is

<p align="center">
<img src="https://render.githubusercontent.com/render/math?math=p_h(t) = A \cdot sin(2\pi \cdot M_h \cdot F_N(t))">
</p>














