
class Thread {
    public:
    // Public members (accessible from outside the class)
        pthread_t thread;
        int uid;
        bool started;
        //Thread( int val );
        void start();
        void stop();
        void done();
        int id();
};