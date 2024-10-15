#ifndef PIPE_H
#define PIPE_H


class Pipe {
private:
    int capacity;
    int flow = 0;
public:
    explicit Pipe(const int& capacity);
    [[nodiscard]] int getCapacity() const;
    [[nodiscard]] int getFlow() const;
    [[nodiscard]] double getRatio() const;
    void setFlow(const int& flow);
    void setCapacity(const int& cap);
};


#endif
