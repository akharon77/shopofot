#include <algorithm>
#include <cstring>

#include "graphics/shapes.hpp"

static const plug::Color White  = plug::Color(255, 255, 255, 255);
static const plug::Color Black  = plug::Color(0, 0, 0, 255);

static const plug::Color Red    = plug::Color(255, 0, 0, 255);
static const plug::Color Green  = plug::Color(0, 255, 0, 255);
static const plug::Color Blue   = plug::Color(0, 0, 255, 255);

static const plug::Color Transparent = plug::Color(0, 0, 0, 0);

static const size_t SYMBOL_WIDTH  = 7ul;
static const size_t SYMBOL_HEIGHT = 7ul;

static const bool UNKNOWN[SYMBOL_WIDTH * SYMBOL_HEIGHT] = 
{
    0, 1, 0, 1, 0, 1, 0,                                     
    0, 0, 1, 0, 1, 0, 0,                                     
    0, 1, 0, 1, 0, 1, 0,                                     
    0, 0, 1, 0, 1, 0, 0,                                     
    0, 1, 0, 1, 0, 1, 0,                                     
    0, 0, 1, 0, 1, 0, 0,                                     
    0, 1, 0, 1, 0, 1, 0                                         
};

static const bool NUMBERS[][SYMBOL_WIDTH * SYMBOL_HEIGHT] = 
{
    {   
        0, 0, 1, 1, 1, 0, 0,                                     
        0, 0, 1, 0, 1, 0, 0,                                     
        0, 0, 1, 0, 1, 0, 0,                                     
        0, 0, 1, 0, 1, 0, 0,                                     
        0, 0, 1, 0, 1, 0, 0,                                     
        0, 0, 1, 0, 1, 0, 0,                                     
        0, 0, 1, 1, 1, 0, 0
    },  

    {   
        0, 0, 0, 1, 0, 0, 0,                                     
        0, 0, 1, 1, 0, 0, 0,                                     
        0, 0, 0, 1, 0, 0, 0,                                     
        0, 0, 0, 1, 0, 0, 0,                                     
        0, 0, 0, 1, 0, 0, 0,                                     
        0, 0, 0, 1, 0, 0, 0,                                     
        0, 0, 0, 1, 0, 0, 0
    },   

    {   
        0, 0, 1, 1, 1, 0, 0,                                     
        0, 0, 0, 0, 1, 0, 0,                                     
        0, 0, 0, 0, 1, 0, 0,                                     
        0, 0, 1, 1, 1, 0, 0,                                     
        0, 0, 1, 0, 0, 0, 0,                                     
        0, 0, 1, 0, 0, 0, 0,                                     
        0, 0, 1, 1, 1, 0, 0
    },      

    {   
        0, 0, 1, 1, 0, 0, 0,                                     
        0, 0, 0, 0, 1, 0, 0,                                     
        0, 0, 0, 0, 1, 0, 0,                                     
        0, 0, 0, 1, 0, 0, 0,                                     
        0, 0, 0, 0, 1, 0, 0,                                     
        0, 0, 0, 0, 1, 0, 0,                                     
        0, 0, 1, 1, 0, 0, 0
    },     

    {   
        0, 0, 1, 0, 1, 0, 0,                                     
        0, 0, 1, 0, 1, 0, 0,                                     
        0, 0, 1, 0, 1, 0, 0,                                     
        0, 0, 1, 1, 1, 0, 0,                                     
        0, 0, 0, 0, 1, 0, 0,                                     
        0, 0, 0, 0, 1, 0, 0,                                     
        0, 0, 0, 0, 1, 0, 0
    },  

    {   
        0, 0, 1, 1, 1, 0, 0,                                     
        0, 0, 1, 0, 0, 0, 0,                                     
        0, 0, 1, 0, 0, 0, 0,                                     
        0, 0, 1, 1, 1, 0, 0,                                     
        0, 0, 0, 0, 1, 0, 0,                                     
        0, 0, 0, 0, 1, 0, 0,                                     
        0, 0, 1, 1, 1, 0, 0
    },      

    {   
        0, 0, 1, 1, 1, 0, 0,                                     
        0, 0, 1, 0, 0, 0, 0,                                     
        0, 0, 1, 0, 0, 0, 0,                                     
        0, 0, 1, 1, 1, 0, 0,                                     
        0, 0, 1, 0, 1, 0, 0,                                     
        0, 0, 1, 0, 1, 0, 0,                                     
        0, 0, 1, 1, 1, 0, 0
    },         

    {   
        0, 0, 1, 1, 1, 0, 0,                                     
        0, 0, 0, 0, 1, 0, 0,                                     
        0, 0, 0, 0, 1, 0, 0,                                     
        0, 0, 0, 0, 1, 0, 0,                                     
        0, 0, 0, 0, 1, 0, 0,                                     
        0, 0, 0, 0, 1, 0, 0,                                     
        0, 0, 0, 0, 1, 0, 0
    },     

    {   
        0, 0, 1, 1, 1, 0, 0,                                     
        0, 0, 1, 0, 1, 0, 0,                                     
        0, 0, 1, 0, 1, 0, 0,                                     
        0, 0, 1, 1, 1, 0, 0,                                     
        0, 0, 1, 0, 1, 0, 0,                                     
        0, 0, 1, 0, 1, 0, 0,                                     
        0, 0, 1, 1, 1, 0, 0
    },     

    {   
        0, 0, 1, 1, 1, 0, 0,                                     
        0, 0, 1, 0, 1, 0, 0,                                     
        0, 0, 1, 0, 1, 0, 0,                                     
        0, 0, 1, 1, 1, 0, 0,                                     
        0, 0, 0, 0, 1, 0, 0,                                     
        0, 0, 0, 0, 1, 0, 0,                                     
        0, 0, 0, 0, 1, 0, 0
    },        
};

static const bool QUESTION_MARK[SYMBOL_WIDTH * SYMBOL_HEIGHT] = 
{
    0, 0, 0, 1, 0, 0, 0,                                     
    0, 0, 1, 0, 1, 0, 0,                                     
    0, 0, 0, 0, 1, 0, 0,                                     
    0, 0, 0, 1, 0, 0, 0,                                     
    0, 0, 0, 1, 0, 0, 0,                                     
    0, 0, 0, 0, 0, 0, 0,                                     
    0, 0, 0, 1, 0, 0, 0  
};

static const bool EXCLAMATION_MARK[SYMBOL_WIDTH * SYMBOL_HEIGHT] = 
{
    0, 0, 0, 1, 0, 0, 0,                                     
    0, 0, 0, 1, 0, 0, 0,                                     
    0, 0, 0, 1, 0, 0, 0,                                     
    0, 0, 0, 1, 0, 0, 0,                                     
    0, 0, 0, 1, 0, 0, 0,                                     
    0, 0, 0, 0, 0, 0, 0,                                     
    0, 0, 0, 1, 0, 0, 0  
};

static const bool DOT[SYMBOL_WIDTH * SYMBOL_HEIGHT] = 
{
    0, 0, 0, 0, 0, 0, 0,                                     
    0, 0, 0, 0, 0, 0, 0,                                     
    0, 0, 0, 0, 0, 0, 0,                                     
    0, 0, 0, 0, 0, 0, 0,                                     
    0, 0, 0, 0, 0, 0, 0,                                     
    0, 0, 0, 0, 0, 0, 0,                                     
    0, 0, 0, 1, 0, 0, 0  
};

static const bool SLASH[SYMBOL_WIDTH * SYMBOL_HEIGHT] = 
{
    0, 0, 0, 0, 1, 0, 0,                                     
    0, 0, 0, 0, 1, 0, 0,                                     
    0, 0, 0, 1, 0, 0, 0,                                     
    0, 0, 0, 1, 0, 0, 0,                                     
    0, 0, 0, 1, 0, 0, 0,                                     
    0, 0, 1, 0, 0, 0, 0,                                     
    0, 0, 1, 0, 0, 0, 0  
};

static const bool SPACE[SYMBOL_WIDTH * SYMBOL_HEIGHT] = 
{
    0, 0, 0, 0, 0, 0, 0,                                     
    0, 0, 0, 0, 0, 0, 0,                                     
    0, 0, 0, 0, 0, 0, 0,                                     
    0, 0, 0, 0, 0, 0, 0,                                     
    0, 0, 0, 0, 0, 0, 0,                                     
    0, 0, 0, 0, 0, 0, 0,                                     
    0, 0, 0, 0, 0, 0, 0  
};

static const bool LETTERS[][SYMBOL_WIDTH * SYMBOL_HEIGHT] = 
{
    {   
        0, 0, 1, 1, 1, 0, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 1, 1, 1, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0
    },   

    {   
        0, 1, 1, 1, 1, 0, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 0, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 1, 1, 1, 0, 0
    },      

    {   
        0, 0, 1, 1, 1, 0, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 0, 0,                                     
        0, 1, 0, 0, 0, 0, 0,                                     
        0, 1, 0, 0, 0, 0, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 0, 1, 1, 1, 0, 0
    },     

    {   
        0, 1, 1, 1, 0, 0, 0,                                     
        0, 1, 0, 0, 1, 0, 0,                                     
        0, 1, 0, 0, 1, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 1, 1, 0,                                     
        0, 1, 0, 0, 1, 0, 0,                                     
        0, 1, 1, 1, 0, 0, 0
    },  

    {   
        0, 1, 1, 1, 1, 1, 0,                                     
        0, 1, 0, 0, 0, 0, 0,                                     
        0, 1, 0, 0, 0, 0, 0,                                     
        0, 1, 1, 1, 0, 0, 0,                                     
        0, 1, 0, 0, 0, 0, 0,                                     
        0, 1, 0, 0, 0, 0, 0,                                     
        0, 1, 1, 1, 1, 1, 0
    },      

    {   
        0, 1, 1, 1, 1, 1, 0,                                     
        0, 1, 0, 0, 0, 0, 0,                                     
        0, 1, 0, 0, 0, 0, 0,                                     
        0, 1, 1, 1, 0, 0, 0,                                     
        0, 1, 0, 0, 0, 0, 0,                                     
        0, 1, 0, 0, 0, 0, 0,                                     
        0, 1, 0, 0, 0, 0, 0
    },         

    {   
        0, 0, 1, 1, 1, 0, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 0, 0,                                     
        0, 1, 0, 0, 0, 0, 0,                                     
        0, 1, 0, 0, 1, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 0, 1, 1, 1, 0, 0
    },     

    {   
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 1, 1, 1, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0
    },     

    {   
        0, 1, 1, 1, 1, 1, 0,                                     
        0, 0, 0, 1, 0, 0, 0,                                     
        0, 0, 0, 1, 0, 0, 0,                                     
        0, 0, 0, 1, 0, 0, 0,                                     
        0, 0, 0, 1, 0, 0, 0,                                     
        0, 0, 0, 1, 0, 0, 0,                                     
        0, 1, 1, 1, 1, 1, 0
    },    

    {   
        0, 1, 1, 1, 1, 1, 0,                                     
        0, 0, 0, 1, 0, 0, 0,                                     
        0, 0, 0, 1, 0, 0, 0,                                     
        0, 0, 0, 1, 0, 0, 0,                                     
        0, 0, 0, 1, 0, 0, 0,                                     
        0, 1, 0, 1, 0, 0, 0,                                     
        0, 0, 1, 0, 0, 0, 0
    },

    {   
        0, 1, 0, 0, 1, 0, 0,                                     
        0, 1, 0, 1, 0, 0, 0,                                     
        0, 1, 0, 1, 0, 0, 0,                                     
        0, 1, 1, 0, 0, 0, 0,                                     
        0, 1, 0, 1, 0, 0, 0,                                     
        0, 1, 0, 0, 1, 0, 0,                                     
        0, 1, 0, 0, 0, 1, 0
    },      

    {   
        0, 1, 0, 0, 0, 0, 0,                                     
        0, 1, 0, 0, 0, 0, 0,                                     
        0, 1, 0, 0, 0, 0, 0,                                     
        0, 1, 0, 0, 0, 0, 0,                                     
        0, 1, 0, 0, 0, 0, 0,                                     
        0, 1, 0, 0, 0, 0, 0,                                     
        0, 1, 1, 1, 1, 1, 0
    },   

    {   
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 1, 0, 1, 1, 0,                                     
        0, 1, 0, 1, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0
    },      

    {   
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 1, 0, 0, 1, 0,                                     
        0, 1, 0, 1, 0, 1, 0,                                     
        0, 1, 0, 1, 0, 1, 0,                                     
        0, 1, 0, 1, 0, 1, 0,                                     
        0, 1, 0, 0, 1, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0
    },  

    {   
        0, 0, 1, 1, 1, 0, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 0, 1, 1, 1, 0, 0
    },  

    {   
        0, 1, 1, 1, 1, 0, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 1, 1, 1, 0, 0,                                     
        0, 1, 0, 0, 0, 0, 0,                                     
        0, 1, 0, 0, 0, 0, 0,                                     
        0, 1, 0, 0, 0, 0, 0
    },          

    {   
        0, 0, 1, 1, 0, 0, 0,                                     
        0, 1, 0, 0, 1, 0, 0,                                     
        0, 1, 0, 0, 1, 0, 0,                                     
        0, 1, 0, 0, 1, 0, 0,                                     
        0, 1, 0, 1, 1, 0, 0,                                     
        0, 1, 0, 0, 1, 0, 0,                                     
        0, 0, 1, 1, 0, 1, 0
    },       

    {   
        0, 1, 1, 1, 1, 0, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 1, 1, 1, 0, 0,                                     
        0, 1, 1, 0, 0, 0, 0,                                     
        0, 1, 0, 1, 0, 0, 0,                                     
        0, 1, 0, 0, 1, 0, 0
    },   

    {   
        0, 0, 1, 1, 1, 0, 0,                                     
        0, 1, 0, 0, 0, 0, 0,                                     
        0, 1, 0, 0, 0, 0, 0,                                     
        0, 0, 1, 1, 1, 0, 0,                                     
        0, 0, 0, 0, 0, 1, 0,                                     
        0, 0, 0, 0, 0, 1, 0,                                     
        0, 1, 1, 1, 1, 0, 0
    },     

    {   
        0, 1, 1, 1, 1, 1, 0,                                     
        0, 0, 0, 1, 0, 0, 0,                                     
        0, 0, 0, 1, 0, 0, 0,                                     
        0, 0, 0, 1, 0, 0, 0,                                     
        0, 0, 0, 1, 0, 0, 0,                                     
        0, 0, 0, 1, 0, 0, 0,                                     
        0, 0, 0, 1, 0, 0, 0
    },    

    {   
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 0, 1, 1, 1, 0, 0
    },    

    {   
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 0, 1, 0, 1, 0, 0,                                     
        0, 0, 1, 0, 1, 0, 0,                                     
        0, 0, 1, 0, 1, 0, 0,                                     
        0, 0, 0, 1, 0, 0, 0,                                     
        0, 0, 0, 1, 0, 0, 0
    },    

    {   
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 0, 1, 0, 1, 0,                                     
        0, 1, 0, 1, 0, 1, 0,                                     
        0, 0, 1, 0, 1, 0, 0
    }, 

    {   
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 1, 1, 0, 1, 1, 0,                                     
        0, 0, 1, 0, 1, 0, 0,                                     
        0, 0, 0, 1, 0, 0, 0,                                     
        0, 0, 1, 0, 1, 0, 0,                                     
        0, 1, 1, 0, 1, 1, 0,                                     
        0, 1, 0, 0, 0, 1, 0
    },    

    {   
        0, 1, 0, 0, 0, 1, 0,                                     
        0, 0, 1, 0, 1, 0, 0,                                     
        0, 0, 0, 1, 0, 0, 0,                                     
        0, 0, 0, 1, 0, 0, 0,                                     
        0, 0, 0, 1, 0, 0, 0,                                     
        0, 0, 0, 1, 0, 0, 0,                                     
        0, 0, 0, 1, 0, 0, 0
    }, 

    {   
        0, 1, 1, 1, 1, 1, 0,                                     
        0, 0, 0, 0, 0, 1, 0,                                     
        0, 0, 0, 0, 1, 0, 0,                                     
        0, 0, 0, 1, 0, 0, 0,                                     
        0, 0, 1, 0, 0, 0, 0,                                     
        0, 1, 0, 0, 0, 0, 0,                                     
        0, 1, 1, 1, 1, 1, 0
    }, 
};

void drawLine(plug::RenderTarget &target, 
        const plug::Vec2d &begin, const plug::Vec2d &end,
        const plug::Color color)
{
    plug::VertexArray line(plug::PrimitiveType::Lines, 2);

    line[0] = plug::Vertex(begin, plug::Vec2d(0, 0), color);
    line[1] = plug::Vertex(end,   plug::Vec2d(0, 0), color);

    target.draw(line);
}

void drawCircle(plug::RenderTarget &target,
        const plug::Vec2d &pos, const double radius,
        const plug::Color color)
{
    plug::VertexArray circle(plug::PrimitiveType::LineStrip, 0);

    const size_t cnt = 360;
    double step = 2.0 * M_PI / static_cast<double>(cnt);

    double alpha = 0;
    for (size_t it = 0; it <= cnt; it++)
    {
        plug::Vertex next_vertex(plug::Vec2d(cos(alpha) * radius + pos.x, 
                sin(alpha) * radius + pos.y), 
                Vec2d(0, 0), color);
        circle.appendVertex(next_vertex);
        alpha += step;
    }

    target.draw(circle);  
}


void drawRectangle(plug::RenderTarget &target, 
        const plug::Vec2d &left_up, const plug::Vec2d &right_down,
        const plug::Color color)
{
    plug::VertexArray rectangle(plug::PrimitiveType::LineStrip, 5);

    rectangle[0] = rectangle[4] = plug::Vertex(left_up, plug::Vec2d(0, 0), color);
    rectangle[1] = plug::Vertex(plug::Vec2d(right_down.x, left_up.y), plug::Vec2d(0, 0), color);
    rectangle[2] = plug::Vertex(right_down, plug::Vec2d(0, 0), color);
    rectangle[3] = plug::Vertex(plug::Vec2d(left_up.x, right_down.y), plug::Vec2d(0, 0), color);

    target.draw(rectangle);
}

static void getSymbolTexture(plug::Color *data, const char symbol, const plug::Color color)
{
    const bool *mask = UNKNOWN;

    switch (symbol)
    {
        case '.':
            mask = DOT;
            break;

        case '!':
            mask = EXCLAMATION_MARK;
            break;

        case '?':
            mask = QUESTION_MARK;
            break;

        case '/':
            mask = SLASH;
            break;

        case ' ':
        case '\0':
            mask = SPACE;
            break;

        default:
            {
                if (symbol >= '0' && symbol <= '9')
                {
                    mask = NUMBERS[symbol - '0'];
                }

                if (symbol >= 'a' && symbol <= 'z')
                {
                    mask = LETTERS[symbol - 'a'];
                }

                if (symbol >= 'A' && symbol <= 'Z')
                {
                    mask = LETTERS[symbol - 'A'];
                }
            }
            break;
    }

    for (size_t it = 0; it < SYMBOL_WIDTH * SYMBOL_HEIGHT; ++it)
    {
        if (mask[it])
        {
            data[it] = color;
        }
        else
        {
            data[it] = Transparent;
        }
    }
}

void drawText(plug::RenderTarget &target,
        const plug::Vec2d &pos, 
        const char *text, const double thickness,
        const plug::Color color)
{
    size_t len = strlen(text);

    if (len == 0) return;

    plug::VertexArray vertex_array(plug::Quads, 4);
    vertex_array[0].tex_coords = plug::Vec2d(0, 0);
    vertex_array[1].tex_coords = plug::Vec2d(SYMBOL_WIDTH, 0);
    vertex_array[2].tex_coords = plug::Vec2d(SYMBOL_WIDTH, SYMBOL_HEIGHT);
    vertex_array[3].tex_coords = plug::Vec2d(0, SYMBOL_HEIGHT);

    plug::Color *data = new plug::Color[SYMBOL_WIDTH * SYMBOL_HEIGHT];

    double offset = SYMBOL_WIDTH * thickness;

    for (size_t it = 0; it < len; it++)
    {
        getSymbolTexture(data, text[it], color);

        plug::Texture texture(SYMBOL_WIDTH, SYMBOL_HEIGHT, data);

        plug::Vec2d size(thickness * SYMBOL_WIDTH, thickness * SYMBOL_HEIGHT);

        vertex_array[0].position = plug::Vec2d(pos.x + it * offset, pos.y);
        vertex_array[1].position = plug::Vec2d(pos.x + it * offset + size.x, pos.y);
        vertex_array[2].position = plug::Vec2d(pos.x + it * offset + size.x, pos.y + size.y);
        vertex_array[3].position = plug::Vec2d(pos.x + it * offset, pos.y + size.y);

        target.draw(vertex_array, texture);
    }

    delete[] data;
}

