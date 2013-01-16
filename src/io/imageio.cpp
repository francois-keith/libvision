#include <vision/io/imageio.h>

namespace vision
{

template<>
void save_color<uint16_t, vision::DEPTH> ( std::string filename , Image<uint16_t, vision::DEPTH> * img)
{
    vision::Image<uint32_t, vision::RGB> * out = new vision::Image<uint32_t, vision::RGB>(img->size);
    const unsigned int MAX_DEPTH = 10000;
    unsigned int histo[MAX_DEPTH];
    memset(histo, 0, MAX_DEPTH*sizeof(unsigned int));
    for(size_t p = 0; p < img->pixels; ++p)
    {
        histo[img->raw_data[p]]++;
    }
    unsigned int nbPoints = img->pixels - histo[0];
    histo[0] = 0;
    if(nbPoints)
    {
        for(size_t c = 1; c < MAX_DEPTH; ++c)
        {
            histo[c] += histo[c-1];
        }
        for(size_t c = 1; c < MAX_DEPTH; ++c)
        {
            histo[c] = (unsigned int)(256 * (1.0f - ((float)histo[c] / nbPoints)));
        }
    }
    for(size_t p = 0; p < img->pixels; ++p)
    {
        out->raw_data[p] = histo[img->raw_data[p]];
    }
    save_color<uint32_t, vision::RGB>(filename, out);
    delete out;
}

} // namespace vision
