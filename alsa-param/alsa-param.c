#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <alsa/asoundlib.h>
#include <alloca.h>

struct channel_t
{
    snd_mixer_selem_channel_id_t id;
    const char *name;
};

struct channel_t channel_list[] =
{
    { SND_MIXER_SCHN_UNKNOWN, "Unknown" },
    { SND_MIXER_SCHN_FRONT_LEFT, "Front left" },
    { SND_MIXER_SCHN_FRONT_RIGHT, "Front right" },
    { SND_MIXER_SCHN_REAR_LEFT, "Rear left" },
    { SND_MIXER_SCHN_REAR_RIGHT, "Rear right" },
    { SND_MIXER_SCHN_FRONT_CENTER, "Front center" },
    { SND_MIXER_SCHN_WOOFER, "Woofer" },
    { SND_MIXER_SCHN_SIDE_LEFT, "Side Left" },
    { SND_MIXER_SCHN_SIDE_RIGHT, "Side Right" },
    { SND_MIXER_SCHN_REAR_CENTER, "Rear Center" },
    //{ SND_MIXER_SCHN_MONO, "Mono (Front left alias)" },
};

#define NUM_CHANNELS    sizeof(channel_list)/sizeof(channel_list[0])

void dump_elements(snd_ctl_t *ctl)
{
    snd_ctl_elem_list_t *clist;

    snd_ctl_elem_list_malloc(&clist);

    snd_ctl_elem_list(ctl, clist);
    snd_ctl_elem_list_alloc_space(clist, snd_ctl_elem_list_get_count(clist));

    int nb_used = snd_ctl_elem_list_get_used(clist);
    for(int i = 0; i < nb_used; i++)
    {
        printf("  +-name: %s\n", snd_ctl_elem_list_get_name(clist, i));
    }
    
    snd_ctl_elem_list_free_space(clist);
    snd_ctl_elem_list_free(clist);
}

void dump_pcm_info(snd_pcm_info_t *info)
{
    printf("  +-pcm\n");
    printf("    +-id: %s\n", snd_pcm_info_get_id(info));
    printf("    +-name: %s\n", snd_pcm_info_get_name(info));
    printf("    +-subdevice name: %s\n", snd_pcm_info_get_subdevice_name(info));
    printf("    +-device: %d\n", snd_pcm_info_get_device(info));
    printf("    +-subdevice: %d\n", snd_pcm_info_get_subdevice(info));
    printf("    +-class: 0x%x\n", snd_pcm_info_get_class(info));
    printf("    +-subclass: 0x%x\n", snd_pcm_info_get_subclass(info));
    printf("    +-subdevices count: %d\n", snd_pcm_info_get_subdevices_count(info));
    printf("    +-subdevices avail: %d\n", snd_pcm_info_get_subdevices_avail(info));
}

void dump_pcm_device(snd_ctl_t *ctl, int dev)
{
    snd_pcm_info_t *info;

    snd_pcm_info_malloc(&info);
    snd_pcm_info_set_device(info, dev);
    
    snd_pcm_info_set_stream(info, SND_PCM_STREAM_CAPTURE);
    snd_pcm_info_set_subdevice(info, 0);
    snd_ctl_pcm_info(ctl, info);
    for(unsigned i = 0; i < snd_pcm_info_get_subdevices_count(info); i++)
    {
        snd_pcm_info_set_subdevice(info, i);
        snd_ctl_pcm_info(ctl, info);
        dump_pcm_info(info);
    }

    snd_pcm_info_set_stream(info, SND_PCM_STREAM_PLAYBACK);
    snd_pcm_info_set_subdevice(info, 0);
    snd_ctl_pcm_info(ctl, info);
    for(unsigned i = 0; i < snd_pcm_info_get_subdevices_count(info); i++)
    {
        snd_pcm_info_set_subdevice(info, i);
        snd_ctl_pcm_info(ctl, info);
        dump_pcm_info(info);
    }

    snd_pcm_info_free(info);
}

void dump_pcm_devices(snd_ctl_t *ctl)
{
    int dev = -1;
    
    while(snd_ctl_pcm_next_device(ctl, &dev) == 0 && dev != -1)
    {
        dump_pcm_device(ctl, dev);
    }
}

void dump_mixer(int card)
{
    snd_mixer_t *mixer;
    char buf[10];

    snd_mixer_open(&mixer, 0);

    sprintf(buf, "hw:%d\n", card);
    snd_mixer_attach(mixer, buf);

    snd_mixer_selem_register(mixer, NULL, NULL);

    snd_mixer_load(mixer);

    /*
    int count = snd_mixer_poll_descriptors_count(mixer);
    struct pollfd *desc = malloc(sizeof(struct pollfd) * count);
    
    snd_mixer_poll_descriptors(mixer, desc, count);

    for(int i = 0; i < count; i++)
    {
        
    }

    free(desc);
    */
    snd_mixer_elem_t *elem = snd_mixer_first_elem(mixer);
    for(; elem; elem = snd_mixer_elem_next(elem))
    {
        printf("  +-%s\n", snd_mixer_selem_get_name(elem));
        printf("    +-playback channels:");
        for(unsigned i = 0; i < NUM_CHANNELS; i++)
            if(snd_mixer_selem_has_playback_channel(elem, channel_list[i].id))
                printf(" %s,", channel_list[i].name);
        printf("\n");
        printf("    +-capture channels:");
        for(unsigned i = 0; i < NUM_CHANNELS; i++)
            if(snd_mixer_selem_has_playback_channel(elem, channel_list[i].id))
                printf(" %s,", channel_list[i].name);
        printf("\n");
        if(snd_mixer_selem_has_common_volume(elem))
            printf("    +-common volume\n");
        if(snd_mixer_selem_has_capture_volume(elem))
            printf("    +-capture volume\n");
        if(snd_mixer_selem_has_playback_volume(elem))
            printf("    +-playback volume\n");
        if(snd_mixer_selem_has_common_switch(elem))
            printf("    +-common switch\n");
        if(snd_mixer_selem_has_capture_switch(elem))
        {
            printf("    +-capture switch (%s)\n",
                snd_mixer_selem_has_capture_switch_joined(elem) ? "joined"
                : "per channel");
        }
        if(snd_mixer_selem_has_playback_switch(elem))
        {
            printf("    +-playback switch (%s)\n",
                snd_mixer_selem_has_playback_switch_joined(elem) ? "joined"
                : "per channel");
        }
        if(snd_mixer_selem_is_enumerated(elem))
        {
            printf("    +-values\n");
            int count = snd_mixer_selem_get_enum_items(elem);
            for(int i = 0; i < count; i++)
            {
                char name[256];
                snd_mixer_selem_get_enum_item_name(elem, i, 256, name);
                printf("      +-%s\n", name);
            }
        }
    }

    snd_mixer_close(mixer);
}

void dump_card(int card)
{
    char buf[10];
    snd_ctl_t *ctl;
    snd_ctl_card_info_t *info;
    int err;

    snd_ctl_card_info_malloc(&info);
    sprintf(buf, "hw:%d", card);

    err = snd_ctl_open(&ctl, buf, 0);
    if(err != 0)
    {
        printf("  +-error: %s\n", snd_strerror(err));
        goto Lend;
    }

    err = snd_ctl_card_info(ctl, info);
    
    if(err != 0)
    {
        printf("  +-error: %s\n", snd_strerror(err));
        goto Lend;
    }

    printf("  +-id: %s\n", snd_ctl_card_info_get_id(info));
    printf("  +-name: %s\n", snd_ctl_card_info_get_name(info));
    printf("  +-long name: %s\n", snd_ctl_card_info_get_longname(info));
    printf("  +-mixer name: %s\n", snd_ctl_card_info_get_mixername(info));
    printf("  +-driver: %s\n", snd_ctl_card_info_get_driver(info));
    printf("  +-components: %s\n", snd_ctl_card_info_get_components(info));

    dump_elements(ctl);
    dump_pcm_devices(ctl);
    dump_mixer(card);

    Lend:
    snd_ctl_close(ctl);
    snd_ctl_card_info_free(info);
}

void dump_cards()
{
    int card = -1;

    while(snd_card_next(&card) == 0 && card != -1)
    {
        printf("+-hw:%d\n", card);

        dump_card(card);
    }
}

const char *type_str(snd_ctl_elem_type_t type)
{
    switch(type)
    {
        case SND_CTL_ELEM_TYPE_BOOLEAN: return "bool";
        case SND_CTL_ELEM_TYPE_INTEGER: return "int";
        case SND_CTL_ELEM_TYPE_ENUMERATED: return "enum";
        default: return "unk";
    }
}

void dump_controls()
{
    snd_ctl_t *ctl;
    snd_ctl_elem_list_t *list;
    snd_ctl_elem_info_t *info;
    snd_ctl_elem_list_alloca(&list);
    snd_ctl_elem_info_alloca(&info);
    if(snd_ctl_open(&ctl, "default", 0) < 0)
    {
        printf("Cannot open ctl\n");
        return;
    }
    if(snd_ctl_elem_list(ctl, list) < 0)
    {
        printf("Cannot get element list\n");
        goto Lend;
    }
    int count = snd_ctl_elem_list_get_count(list);
    if(snd_ctl_elem_list_alloc_space(list, count) < 0)
    {
        printf("Cannot allocate space for element list\n");
        goto Lend;
    }
    if(snd_ctl_elem_list(ctl, list) < 0)
    {
        snd_ctl_elem_list_free_space(list);
        printf("Cannot get element list\n");
        goto Lend;
    }
    for(int i = 0; i < count; i++)
    {
        snd_ctl_elem_id_t *id;
        snd_ctl_elem_id_alloca(&id);
        snd_ctl_elem_list_get_id(list, i, id);

        printf("control %d: %s\n", snd_ctl_elem_id_get_numid(id), snd_ctl_elem_id_get_name(id));

        snd_ctl_elem_info_set_id(info, id);
        snd_ctl_elem_info(ctl, info);
        printf("  type=%s, values=%d\n", type_str(snd_ctl_elem_info_get_type(info)),
            snd_ctl_elem_info_get_count(info));
    }
    snd_ctl_elem_list_free_space(list);
Lend:
    snd_ctl_close(ctl);
}

int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    //dump_cards();
    dump_controls();

    return 0;
}
