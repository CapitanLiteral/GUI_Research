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
    You can check this page that shows some different animations and transitions very clearly:  <a href="https://semantic-ui.com/modules/transition.html#/definition"></a>https://semantic-ui.com/modules/transition.html#/definition</p>


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

<p>Now we have all animations and transitions declared in the enum we want to store all the relations between ui events and the animations and transition so that when one of those events is broadcasted we can react to it. Not all events will have a reaction for all elements as many times it makes no sense.
    In order to store all the relations will use a map using as a key the event, this way when when an event is catched in a certain element it will search in this map if it must react in a certain way (will get into this later).
</p>

```
std::map<gui_events, staticAnim_or_transition> transAndAnimations;
```

<p>Once the map is created we will define some suport methods to add or remove relations between events and animations. We can do some more support methods, here we show some:</p>
```
    void AddAnimationOrTransition(gui_events eventToReact, staticAnim_or_transition animOrTransition);
    void RemoveAnimationOrTransitionReaction(gui_events eventToReact);
    void GetAllAnimationAndTransitions(\std::vector\<\std::pair\<gui_events, staticAnim_or_transition>>& animsAndTrans);
    bool HasEventReactionSet(gui_events eventToReact);
    staticAnim_or_transition GetAnimOrTransitionForEvent(gui_events eventToReact);
```
<p>
As we will be searching in the map with map::find and its a heavy method we used a optional variable tha starores if an event has set a reaction, this way before searching in the map we can look in this variable and if we get that there is a reaction to that event we then search in the map and if not we won’t do the search. Is not a big improvment as the map doesn’t get really big but can be a cool way to practise bit operations.
As i have said before will use bit operations to know if a concret element has a reaction to a concret event. If you have looked in the code you have probably seen this:</p>

```
enum gui_events
{
    EVENT_NONE = 0,
    LISTENING_END = (1 << 0),
    MOUSE_ENTERS = (1 << 1),
    MOUSE_LEAVES = (1 << 2),
    MOUSE_LCLICK_DOWN = (1 << 3),
    MOUSE_LCLICK_UP = (1 << 4),
    MOUSE_RCLICK_DOWN = (1 << 5),
    MOUSE_RCLICK_UP = (1 << 6),
    GAIN_FOCUS = (1 << 7),
    LOST_FOUCS = (1 << 8),
    INPUT_CHANGED = (1 << 9),
    INPUT_SUBMIT = (1 << 10),
    VALUE_CHANGED = (1 << 11),
    RETURN_DOWN = (1 << 12),

    ENABLE = (1 << 13),
    DISABLE = (1 << 14),

};
```

<p>We have defined all events in an enum so we create a gui_events variable in our GUIElement and will call it “eventsToReact”. You can see that in each state in this enum there is something like this:</p>
```
(1 << n)
```
<p>, this means we move a bit to the left n positions, so:</p>

```
    (1 << 0) = 00001 = 1
    (1 << 1) = 00010 = 2
    (1 << 2) = 00100 = 4
    (1 << 3) = 01000 = 8
    (1 << 4) = 10000 = 16
```

<p>as you can see now each event is represented by a number that in binary is full of 0 less one bit that is not repeated in any other case. Now you may ask why this will help us so here we go. Do you remember the variable we told you to create before named “eventsToReact”?
By default this variable will be equal to 0 what means EVENT_NONE. Each time we add a reaction to the element we will add into this variable the event passed using bit operations:</p>

```
    eventsToReact = (gui_events)(eventsToReact | newEventToReact);

```

<p>You can see that we must cast the operation as it is internally doing a bit operation with ints but what does this mean? Supose before this events to react was ...000 and we added a reaction to the event MOUSE_LCLICK_DOWN which have the number 01000 = 8. After this operation eventsToReact now is equal to 01000. Now we add a reaction to another event like MOUSE_ENTERS. After adding this event eventsToReact’s value is 01010 = 10. You can se that the previous bit we added hasn’t been modified. Later on the code we will be able to look in the desired bit of this variable if is one()we have a reaction) or zero(we don’t have a reaction).</p>

<p>Now you can add those bits you will have to remove them if a reaction is removed from the map. As this is just an optional feature we will let you investigate how to remove it and how to check in the variable if a certain event is stored there. Here we let you a pair of links might help you:
<ul>
    <li><a href="http://www.cprogramming.com/tutorial/bitwise_operators.html">https://semantic-ui.com/modules/transition.html#/definition</a></li>
    <li><a href="http://www.learncpp.com/cpp-tutorial/38-bitwise-operators/">https://semantic-ui.com/modules/transition.html#/definition</a></li>
</ul>

If you don’t want to investigate it or you can’t understand it you can check the solution and ask us if you need any help.</p>


<p>Okey,we have the map filled with all reactions but now what? You might have seen a method in the GUIElement class called OnGuiEvent. This method is called from the ui module when an element is involved with an event and notifies it of which event the same way that the module notifies all the element’s listeners. Before going on create to variables of type staticAnim_or_transition and called them currentStaticAnimation and currentTransition and set their value as SAT_NONE by default. Now search in the map if there is a reaction to the received event, remember the eventsToReac variable if you want to use this feature.
    If we can’t find a reaction just go on and do nothing. If we find a reaction we will have to determine if its an animation or a transition, to discover this we will use a simple trick, look again the staticAnim_or_transition enum, you can see a state called SAT_SEPARATOR that does exactly what it’s name says. As an enum is a number we can check if the given reaction is lower or higher than the separator and depending on how you have created the enum you will know if that’s an animation or a transition and assign currentStatic animation or currentTransition to the value you got.</p>

<p>We will need a few methods now, at least one for each animation we want and at least another one for each transition. They can be all void and can recieve a float to know the frame dt.</p>

<p>Move now to the element Update, here we will look both variables currentStaticAnimation and currentTransition with a switch and each case call the method it’s assosiated:</p>

```
if (currentStaticAnimation != SAT_NONE)
{
//Do here the animation according the active one.

switch (currentStaticAnimation)
{
    case SA_FLASH:
        FlashSA(dt);
    break;
    case SA_SHAKE:
        ShakeSA(dt);
    break;
    case SA_PULSE:
        PulseSA(dt);
    break;
    case SA_BOUNCE:
        BounceSA(dt);
    break;
    }

    }

if (currentTransition != SAT_NONE)
{
//DO here the transition logic according the one active.

    switch (currentTransition)
    {
    case T_SCALE:
        ScaleT(dt);
    break;
    case T_FADE:
        FadeT(dt);
    break;
    case T_DROP:
        DropT(dt);
    break;
    case T_FLY:
        FlyT(dt);
    break;
    case T_SLIDE:
        SlideT(dt);
    break;
    case T_MOVE_RIGHT:
        MoveRightT(dt);
    break;
    case T_MOVE_LEFT:
        MoveLeftT(dt);
    break;
    case T_MOVE_UP:
        MoveUpT(dt);
    break;
    case T_MOVE_DOWN:
        MoveDownT(dt);
    break;
    }
    }
```

<p>From here untill the end you can do the animations as you want but remember that untill you don’t change the value of currentStaticAnimation and/or currentTransition to SAT_NONE the realted methods will be called every frame. </p>

<p>Here we will explain how we have done some animations and transitions but take into account that you can adapt the number of animations and transitions to your needs.</p>







