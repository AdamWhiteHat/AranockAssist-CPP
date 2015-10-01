Aranock Assist - C++ - ReadProcessMemory Macro
=============
NOTE: This is here primarily for archival and historical purposes. This is not an example of good code; all of the logic is contained within the file AranockAssistDlg.cpp. Using modern technologies, if I had to re-implement this program, I would wrap the ReadProcessMemory in a COM library, and call it from C#. Then I would poll the values every 80ms and wire them to an event. Wire the start and stop of timers that track certain refresh/wait periods such as spell fatigue or cast spells. I would take all these event streams as IObservable<T> and compose these event streams using a powerful, & simple query syntax using LINQ and Reactive Extentions. This would be the best way to compose triggers for complex conditions.
=============

Game macro/playing/cheat program for Aranock (Like Mercenaries of Astonia).
 - www.aranock-online.co.uk
 - www.google.com/search?tbm=isch&q=aranock+online

Using ReadProcessMemory, it reads the memory address for health, mana, endurance and can respond to that by casting spell or drinking a potion.
Other features include:
 - Auto-spell, based on a timer.
 - Auto-mine, using mouse clicks.
