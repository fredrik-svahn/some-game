#include <string>
#include "./include/GL/gl.h"
#include "./include/GL/glu.h"
#include "./include/GL/glut.h"
#include "./include/GL/freeglut.h"
#include "./include/GL/glext.h"
#include "./include/GL/glew.h"
#include "./include/stb_image.h"
#include <unordered_map>
struct Asset {
    std::unordered_map<std::string, unsigned int> ids;

    void load(const char* file, std::string name) {
        unsigned int texture;
        int width, height, nrChannels;
        unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

    }
};
