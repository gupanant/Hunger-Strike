#ifndef SPRITE_H
#define SPRITE_H



class Sprite
{
    public:
        Sprite();
        virtual ~Sprite();

        float sprit_size[3]={1.0,1.0,1.0};
        float sprite_x;
        float sprit_y;
        float Vertices[4][3] ={ {0.0, 0.0, -1.5},{1.0, 0.0, -1.5},{1.0, 1.0, -1.5},{0.0, 1.0, -1.5}};
        void draw_sprite();
        void SpriteInit(char *);
        void Action(int);

        int RunSpeed =0;
        int jumpspped = 0;
        int actionTrigger=0;

    protected:

    private:
};

#endif // SPRITE_H
