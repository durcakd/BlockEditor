#ifndef COMMAND_H
#define COMMAND_H




class Command {
public:
    explicit Command();

    virtual void execute() const = 0;

protected:

};

#endif
