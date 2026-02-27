#pragma once

class Animated {
    private:
        bool finished;
        bool exiting;
        
    protected:
        explicit Animated() : finished(false), exiting(false) {}
    
    public:
        virtual void done( const bool flag ) {
            this->finished = flag;
        }
        
        virtual void quit( const bool flag ) {
            this->exiting = flag;
        }
        
        virtual bool done() const {
            return this->finished;
        }
        
        virtual bool quit() const {
            return this->exiting;
        }
};