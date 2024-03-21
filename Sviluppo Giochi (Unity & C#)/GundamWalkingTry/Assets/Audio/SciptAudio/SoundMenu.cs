using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.Audio;

public class SoundMenu : MonoBehaviour
{
    public AudioMixer audioMixer;
    [SerializeField] private Slider musicSlider;
    [SerializeField] private Slider effectsSlider;


    private void Start()
    {
        if (PlayerPrefs.HasKey("Music")) LoadMusic();
        if (PlayerPrefs.HasKey("Effects")) LoadEffects();
    }

    public void SetVolume (float volume){
        audioMixer.SetFloat("volume", volume);
    }

    public void SetVolumeEffects(float volume)
    {
        audioMixer.SetFloat("Effects", Mathf.Log10(volume)*20);
        PlayerPrefs.SetFloat("Effects",volume);

        Debug.Log("settato mixer effects a:" + Mathf.Log10(volume) * 20);
    }

    public void SetVolumeMusic(float volume)
    {
        audioMixer.SetFloat("Music", Mathf.Log10(volume) * 20);
        PlayerPrefs.SetFloat("Music", volume);

        Debug.Log("settato mixer music a:" + Mathf.Log10(volume) * 20);

    }

    private void LoadMusic() {
        musicSlider.value = PlayerPrefs.GetFloat("Music");
        //Debug.Log("slider music" + musicSlider.value);
        //SetVolumeMusic(musicSlider.value);
       

    }
    private void LoadEffects() {
        effectsSlider.value = PlayerPrefs.GetFloat("Effects");
        //Debug.Log("slider music" + musicSlider.value);
        //SetVolumeEffects(effectsSlider.value);
    }

}
