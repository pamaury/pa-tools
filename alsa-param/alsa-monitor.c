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
    printf("  +-hctl controls\n");
    for(int i = 0; i < nb_used; i++)
    {
        printf("    +-name: %s\n", snd_ctl_elem_list_get_name(clist, i));
    }

    snd_ctl_elem_list_free_space(clist);
    snd_ctl_elem_list_free(clist);
}

void dump_pcm_info(int subdev, snd_pcm_info_t *info)
{
    printf("      +-subdev %d\n", subdev);
    printf("        +-id: %s\n", snd_pcm_info_get_id(info));
    printf("        +-name: %s\n", snd_pcm_info_get_name(info));
    printf("        +-subdevice name: %s\n", snd_pcm_info_get_subdevice_name(info));
    printf("        +-device: %d\n", snd_pcm_info_get_device(info));
    printf("        +-subdevice: %d\n", snd_pcm_info_get_subdevice(info));
    printf("        +-class: 0x%x\n", snd_pcm_info_get_class(info));
    printf("        +-subclass: 0x%x\n", snd_pcm_info_get_subclass(info));
    printf("        +-subdevices count: %d\n", snd_pcm_info_get_subdevices_count(info));
    printf("        +-subdevices avail: %d\n", snd_pcm_info_get_subdevices_avail(info));
}

void dump_pcm_device(snd_ctl_t *ctl, int dev)
{
    snd_pcm_info_t *info;

    snd_pcm_info_malloc(&info);
    snd_pcm_info_set_device(info, dev);

    snd_pcm_info_set_stream(info, SND_PCM_STREAM_CAPTURE);
    snd_pcm_info_set_subdevice(info, 0);
    snd_ctl_pcm_info(ctl, info);
    printf("    +-capture\n");
    for(unsigned i = 0; i < snd_pcm_info_get_subdevices_count(info); i++)
    {
        snd_pcm_info_set_subdevice(info, i);
        snd_ctl_pcm_info(ctl, info);
        dump_pcm_info(i, info);
    }

    snd_pcm_info_set_stream(info, SND_PCM_STREAM_PLAYBACK);
    snd_pcm_info_set_subdevice(info, 0);
    snd_ctl_pcm_info(ctl, info);
    printf("    +-playback\n");
    for(unsigned i = 0; i < snd_pcm_info_get_subdevices_count(info); i++)
    {
        snd_pcm_info_set_subdevice(info, i);
        snd_ctl_pcm_info(ctl, info);
        dump_pcm_info(i, info);
    }

    snd_pcm_info_free(info);
}

void dump_pcm_devices(snd_ctl_t *ctl)
{
    int dev = -1;

    while(snd_ctl_pcm_next_device(ctl, &dev) == 0 && dev != -1)
    {
        printf("  +-pcm %d\n", dev);
        dump_pcm_device(ctl, dev);
    }
}

void dump_mixer(const char *cardname)
{
    snd_mixer_t *mixer;

    snd_mixer_open(&mixer, 0);

    snd_mixer_attach(mixer, cardname);

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
    printf("  +-mixer elements\n");
    snd_mixer_elem_t *elem = snd_mixer_first_elem(mixer);
    for(; elem; elem = snd_mixer_elem_next(elem))
    {
        printf("    +-%s\n", snd_mixer_selem_get_name(elem));
        printf("      +-playback channels:");
        for(unsigned i = 0; i < NUM_CHANNELS; i++)
            if(snd_mixer_selem_has_playback_channel(elem, channel_list[i].id))
                printf(" %s,", channel_list[i].name);
        printf("\n");
        printf("      +-capture channels:");
        for(unsigned i = 0; i < NUM_CHANNELS; i++)
            if(snd_mixer_selem_has_playback_channel(elem, channel_list[i].id))
                printf(" %s,", channel_list[i].name);
        printf("\n");
        if(snd_mixer_selem_has_common_volume(elem))
            printf("      +-common volume\n");
        if(snd_mixer_selem_has_capture_volume(elem))
            printf("      +-capture volume\n");
        if(snd_mixer_selem_has_playback_volume(elem))
            printf("      +-playback volume\n");
        if(snd_mixer_selem_has_common_switch(elem))
            printf("      +-common switch\n");
        if(snd_mixer_selem_has_capture_switch(elem))
        {
            printf("      +-capture switch (%s)\n",
                snd_mixer_selem_has_capture_switch_joined(elem) ? "joined"
                : "per channel");
        }
        if(snd_mixer_selem_has_playback_switch(elem))
        {
            printf("      +-playback switch (%s)\n",
                snd_mixer_selem_has_playback_switch_joined(elem) ? "joined"
                : "per channel");
        }
        if(snd_mixer_selem_is_enumerated(elem))
        {
            printf("      +-values\n");
            int count = snd_mixer_selem_get_enum_items(elem);
            for(int i = 0; i < count; i++)
            {
                char name[256];
                snd_mixer_selem_get_enum_item_name(elem, i, 256, name);
                printf("        +-%s\n", name);
            }
        }
    }

    snd_mixer_close(mixer);
}

void dump_card(const char *cardname)
{
    snd_ctl_t *ctl;
    snd_ctl_card_info_t *info;
    int err;

    snd_ctl_card_info_malloc(&info);
    err = snd_ctl_open(&ctl, cardname, 0);
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
    dump_mixer(cardname);

    Lend:
    snd_ctl_close(ctl);
    snd_ctl_card_info_free(info);
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

void dump_controls(const char *cardname)
{
    snd_ctl_t *ctl;
    snd_ctl_elem_list_t *list;
    snd_ctl_elem_info_t *info;
    snd_ctl_elem_list_alloca(&list);
    snd_ctl_elem_info_alloca(&info);
    if(snd_ctl_open(&ctl, cardname, 0) < 0)
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
    printf("  +-controls\n");
    for(int i = 0; i < count; i++)
    {
        snd_ctl_elem_id_t *id;
        snd_ctl_elem_id_alloca(&id);
        snd_ctl_elem_list_get_id(list, i, id);

        printf("    +-%d\n", snd_ctl_elem_id_get_numid(id));
        printf("      +-name: %s\n", snd_ctl_elem_id_get_name(id));

        snd_ctl_elem_info_set_id(info, id);
        snd_ctl_elem_info(ctl, info);
        printf("      +-type:%s\n", type_str(snd_ctl_elem_info_get_type(info)));
        printf("      +-values: %d\n", snd_ctl_elem_info_get_count(info));
    }
    snd_ctl_elem_list_free_space(list);
Lend:
    snd_ctl_close(ctl);
}

void dump_cards(void)
{
    int card = -1;

    while(snd_card_next(&card) == 0 && card != -1)
    {
        char cardname[32];
        sprintf(cardname, "hw:%d", card);
        printf("+-%s\n", cardname);

        dump_card(cardname);
        dump_controls(cardname);
    }
}

/* find a control element ID by name, return false of not found, the id needs
 * to be allocated */
static bool find_control_by_numid(snd_ctl_t *ctl, snd_ctl_elem_id_t *id, unsigned numid)
{
    snd_ctl_elem_list_t *list;
    /* allocate list on heap because it is used it is used in other functions */
    snd_ctl_elem_list_alloca(&list);
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
    /* ALSA identifies controls by "id"s, it almost makes sense, except ids
     * are a horrible opaque structure */
    count = snd_ctl_elem_list_get_count(list);
    /* enumerate controls */
    for(int i = 0; i < count; i++)
    {
        snd_ctl_elem_list_get_id(list, i, id);

        if(snd_ctl_elem_id_get_numid(id) == numid)
            return true;
    }
    /* not found */
Lend:
    return false;
}

void print_ctl_value(snd_ctl_t *ctl, snd_ctl_elem_id_t *id)
{
    snd_ctl_elem_info_t *info;
    snd_ctl_elem_value_t *value;
    snd_ctl_elem_info_alloca(&info);
    snd_ctl_elem_value_alloca(&value);
    snd_ctl_elem_info_set_id(info, id);
    snd_ctl_elem_value_set_id(value, id);
    snd_ctl_elem_info(ctl, info);
    snd_ctl_elem_type_t type = snd_ctl_elem_info_get_type(info);
    snd_ctl_elem_read(ctl, value);
    for(unsigned i = 0; i < snd_ctl_elem_info_get_count(info); i++)
    {
        if(i != 0)
            printf(", ");
        printf("value[%d]=", i);
        if(type == SND_CTL_ELEM_TYPE_BOOLEAN)
        {
            long val = snd_ctl_elem_value_get_boolean(value, i);
            printf("%s", val ? "On" : "Off");
        }
        else if(type == SND_CTL_ELEM_TYPE_INTEGER)
        {
            long val = snd_ctl_elem_value_get_integer(value, i);
            printf("%ld", val);
        }
        else if(type == SND_CTL_ELEM_TYPE_ENUMERATED)
        {
            unsigned index = snd_ctl_elem_value_get_enumerated(value, i);
            snd_ctl_elem_info_set_item(info, index);
            if(snd_ctl_elem_info(ctl, info) < 0)
                printf("%d", index);
            else
                printf("%s", snd_ctl_elem_info_get_item_name(info));
        }
    }
    printf("\n");
}

void monitor_events(const char *cardname)
{
    snd_ctl_t *ctl;
    snd_ctl_event_t *event;
    struct pollfd *pfds;
    unsigned short *revents;
    snd_ctl_elem_id_t *id;
    snd_ctl_elem_info_t *info;
    /* allocate things on stack to speedup */
    snd_ctl_elem_id_alloca(&id);
    snd_ctl_elem_info_alloca(&info);
    snd_ctl_event_alloca(&event);
    if(snd_ctl_open(&ctl, cardname, 0) < 0)
    {
        printf("Cannot open ctl\n");
        return;
    }
    snd_ctl_subscribe_events(ctl, 1);
    int pfd_count = snd_ctl_poll_descriptors_count(ctl);
    pfds = malloc(sizeof(pfds) * pfd_count);
    revents = malloc(sizeof(short) * pfd_count);
    pfd_count = snd_ctl_poll_descriptors(ctl, pfds, pfd_count);
    while(true)
    {
        if(poll(pfds, pfd_count, -1) <= 0)
        {
            printf("poll() failed: %m\n");
            break;
        }
        snd_ctl_poll_descriptors_revents(ctl, pfds, pfd_count, revents);
        for(int i = 0; i < pfd_count; i++)
        {
            if(!(revents[i] & POLLIN))
                continue;
            if(snd_ctl_read(ctl, event) < 0)
            {
                printf("snd_ctl_read() failed\n");
                break;
            }
            unsigned mask = snd_ctl_event_elem_get_mask(event);
            printf("## Event: mask=0x%x\n", mask);
            if(mask & SND_CTL_EVENT_MASK_VALUE)
            {
                unsigned numid = snd_ctl_event_elem_get_numid(event);
                /* find control */
                bool found = find_control_by_numid(ctl, id, numid);
                printf("   Value changed: numid=%d, name=%s\n", numid,
                    found ? snd_ctl_elem_id_get_name(id) : "??");
                printf("   New value: ");
                print_ctl_value(ctl, id);
                fflush(stdout);
            }
        }
    }

    free(revents);
    free(pfds);
    snd_ctl_close(ctl);
}

int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    printf("alsa monitor\n");
    dump_cards();
    fflush(stdout);
    monitor_events("hw:0");
    printf("alsa monitor done\n");

    return 0;
}
