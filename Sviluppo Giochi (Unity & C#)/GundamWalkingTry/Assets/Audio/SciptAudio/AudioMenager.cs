using UnityEngine.Audio;
using UnityEngine;
using System;

public class AudioMenager : MonoBehaviour
{

    public Sound[] soundtrack;
    public Sound[] sound_effects;
    public AudioMixer audioMixer;
    public static AudioMenager _instance;

    public static AudioMenager Instance
    {
        get
        {
            if (_instance == null)
            {
                _instance = GameObject.FindObjectOfType<AudioMenager>();
                if (_instance == null) Debug.LogError("No PauseMenu in scene");
            }
            return _instance;
        }
    }

    private void Awake()
    {
        if (_instance == null)
        {
            _instance = this;
            GameObject.DontDestroyOnLoad(this.gameObject);
        }
        else
        {
            GameObject.Destroy(this.gameObject);
        }


    }

    private void InitAudioSources()
    {
        foreach (Sound s in soundtrack)
        {
            s.source = gameObject.AddComponent<AudioSource>();
            s.source.clip = s.clip;
            s.source.loop = s.loop;

            s.source.volume = s.volume;
            s.source.pitch = s.pitch;

            s.source.outputAudioMixerGroup = audioMixer.FindMatchingGroups("Master")[0];
            s.source.outputAudioMixerGroup = audioMixer.FindMatchingGroups("Music")[0];
        }

        foreach (Sound s in sound_effects)
        {
            s.source = gameObject.AddComponent<AudioSource>();
            s.source.clip = s.clip;
            s.source.loop = s.loop;

            s.source.volume = s.volume;
            s.source.pitch = s.pitch;

            s.source.outputAudioMixerGroup = audioMixer.FindMatchingGroups("Master")[0];
            s.source.outputAudioMixerGroup = audioMixer.FindMatchingGroups("Effects")[0];
        }
    }

    private void Start() {
        InitAudioSources();
        //Debug.Log("Play Music");
        PlayMusic("BGSoundTrack");
    }

    public void PlayMusic(string name){
        Sound s = Array.Find(soundtrack, sound => sound.name == name);
        s.source.Play();
    }

    public void PlayEffect(string name)
    {
        Sound s = Array.Find(sound_effects, sound => sound.name == name);
        s.source.Play();
    }


}
