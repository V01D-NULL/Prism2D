#pragma once

class Thread
{        
    public:
        int Create(auto (*fn)(), int id = -1);
    
    private:
        int thread_id;
};