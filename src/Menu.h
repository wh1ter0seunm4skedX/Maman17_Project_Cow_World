#pragma once
class Context; // Forward declaration of Context

class Menu {
public:
    // Pass in the global context which contains all the properties to be adjusted
    Menu(Context& context);
    void handleInteraction();
private:
    Context& context;
};

