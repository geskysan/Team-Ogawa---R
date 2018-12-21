using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class StageNumberSetting : MonoBehaviour {

    [SerializeField] StartUpManager m_startUpmanager;

    public enum STAGE
    {
        stage_1,
        stage_2,
        stage_3,
        stage_4,
        stage_5,
        stage_6,
        stage_7,
    }
    [SerializeField] string[] m_stageName;
    [SerializeField] Text m_staeNameText;

    enum SELECTTYPE
    {
        Order,
        Random
    }
    [SerializeField] SELECTTYPE m_SelectType;

    public STAGE m_stage;
    [SerializeField]
    Sprite[] m_stageImage;
    [SerializeField]
    GameObject m_background;
    [SerializeField]
    ParticleSystem[] particle;

    private void Start()
    {
        for (int i = 0; i < m_stageImage.Length; i++)
        {
            if (m_stage == (STAGE)i)
            {
                // ステージの背景を設定
                m_background.GetComponent<Image>().sprite = m_stageImage[i];
                m_startUpmanager.m_background = m_stageImage[i];

                // ステージ名を設定


                if(particle[i] != null)
                {
                    Instantiate(particle[i]);
                    particle[i].Play();
                }

                break;
            }
        }
    }
}
