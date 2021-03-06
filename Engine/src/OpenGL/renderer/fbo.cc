#include "fbo.h"
#include "../../logging/log.h"
#include "../../UI/ui.h"

namespace GLrenderer
{
    GL_FBO::GL_FBO()
    {
        
    }

    void GL_FBO::genFBO()
    {
        const int retries = 4;
        int tried = 0;

        glGenFramebuffers(1, &(this->fbo));
        
        this->genTexture();
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
        else
        {
            Log().warn("could not generate fbo");
        }
        
        this->was_fbo_generated = true;
    }

    void GL_FBO::genTexture()
    {
        glGenTextures(1, &(this->texture));
        glBindTexture(GL_TEXTURE_2D, this->texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        // attach it to currently bound framebuffer object
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->texture, 0);
    }

    void GL_FBO::bindFBO()
    {
        if (!this->was_fbo_generated)
        {
            this->genFBO();
        }
        glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);
    }

    void GL_FBO::unbindFBO()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void GL_FBO::Destroy()
    {
        glDeleteFramebuffers(1, &(this->fbo));
    }

    std::uint32_t GL_FBO::getTex ()
    {
        return this->texture;
    }
}