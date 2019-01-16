using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class StageNumberSetting : MonoBehaviour {

    public enum STAGE
    {
        stage_1,
        stage_2,
        stage_3,
        stage_4,
        stage_5,
        stage_6,
        stage_7,
        stage_max
    }

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
        switch(m_SelectType)
        {
            case SELECTTYPE.Order:
                for (int i = 0; i < m_stageImage.Length; i++)
                {
                    if (m_stage == (STAGE)i)
                    {
                        // ステージの背景を設定
                        m_background.GetComponent<Image>().sprite = m_stageImage[i];

                        // パーティクルを設定
                        if (particle[i] != null)
                        {
                            Instantiate(particle[i]);
                            particle[i].Play();
                        }

                        break;
                    }
                }
                break;

            case SELECTTYPE.Random:
                var random = Random.Range(0, (int)STAGE.stage_max);

                // ステージの背景を設定
                m_background.GetComponent<Image>().sprite = m_stageImage[random];

                // パーティクルを設定
                if (particle[random] != null)
                {
                    Instantiate(particle[random]);
                    particle[random].Play();
                }
                break;
        }


    }
}
