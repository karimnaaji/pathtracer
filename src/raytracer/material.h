#ifndef __MATERIAL_H__
#define __MATERIAL_H__

enum MaterialType { 
    E_DIFFUSE, 
    E_SPECULAR, 
    E_REFRACT 
};

inline MaterialType MaterialByChar(char material) {
    switch(material) {
        case 'd': return E_DIFFUSE; 
        case 's': return E_SPECULAR;
        case 'r': return E_REFRACT;
        default: return (MaterialType) -1;
    }   
}

#endif
