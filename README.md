# GUI_Research

<h1> UI-Data drive. </h1>

<hr>

<h1>UI-Animations and transitions.</h1>

<h2>Introduction.</h2>
<p>Hi there, we are Pere Rifà and Josep Casanovas, two students at CITM currently at second grade on Game development. During our project 2 subject we amust develop a solution to a given development problem or feature. In our case we had to create a system to provide animations and transitions to UI. Before we start we must thank Capitan Literal (//TODO add link) who programmed the UI system we will use as base project.</p>

<p>This guide and the code provided uses C++ and the project given use Visual Studio 2015 but you can take all the source files and compile them by your own.</p>

<h2>Static animations vs. transitions.</h2>
<p>We use animations and transitions in UI to give more feedback to the user depending on his actions and all events related to her user interface. But what is the difference between a transition and a static animation?</p>
<h3>Static animation.</h3>
<p>A static animations is a small animation that at the end doesn’t modify the element, a simple example is a shake or a bounce animation where the element moves a bit around and at the end recovers its position. Good examples are typical animations done when you place the mouse over a button or when you click on a UI element.
</p>

//TODO: Add gif

<h3>Transitions.</h3>
<p>A transition is an animation used to change the status of the element, most usually to enable or disable the element. Modifying its position, size, alpha, etc we can animate a window or a button to not simply disappear or disappear from the screen. 
</p>

//TODO: Add gif

<p>Those animations and transitions will give us a richer UI that provide much more information to the user. 
You can check this page that shows some different animations and transitions very clearly:  <href>https://semantic-ui.com/modules/transition.html#/definition</href></p>


<h2>Introduction to the system.</h2>
<p>As we have said before, we developed the animationa and transition system on a previous UI system so we will explain a few things you may need to know about it.</p>
<p>The system is divided into two main parts, a class called M_Gui wich is the module that manage all the system. The second part is a class called GUIElement whichhh is a base class for all the UI elements such as GUIImage, GUILabel, etc. The module has a a list with all the elements created in thhe app and manages all of them. It manages all the events like mouse clicks, etc; updates all the elements and render them into thhhe screen.</p>
<p>We will be working on the second part, the base class for all elements. This class contains some basic attributes like the type, a rectangle that defines the position and the size, a status and some more we will explain later used in our system. It also have some methods like setters and getters for the attributes, a method to recive events, an update, a virtual draw, and some more we don't really need to care about. Later we will focus on some we will use on animations and transitions</p>

//TODO: Explain a bit the objective

<h2>Let's start.</h2>
<p>First of all we must define all the different animations and transitions we want to do. In order to store all this we will use an enum we call staticAnim_or_transition. We could define one enum for transitions and another one for static animations but we decided to join all in one to make it easier later:  </p>
```

enum staticAnim_or_transition
{
	SAT_NONE = 0,

	SA_FLASH,
	SA_SHAKE,
	SA_PULSE,
	SA_BOUNCE,

	SAT_SEPARATOR,

	T_SCALE,
	T_FADE,
	T_DROP,
	T_FLY,
	T_SLIDE,
	T_MOVE_RIGHT,
	T_MOVE_LEFT,
	T_MOVE_UP,
	T_MOVE_DOWN
};

```






