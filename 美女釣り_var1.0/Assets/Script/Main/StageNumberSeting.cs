using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class StageNumberSeting : MonoBehaviour {

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
                m_background.GetComponent<Image>().sprite = m_stageImage[i];
                Instantiate(particle[i]);
                particle[i].Play();
                break;
            }
        }

        //switch (m_SelectType)
        //{
        //    case SELECTTYPE.Order:
        //        for (int i = 0; i < m_stageImage.Length; i++)
        //        {
        //            if (m_stage == (STAGE)i)
        //            {
        //                m_background.GetComponent<Image>().sprite = m_stageImage[i];
        //                Instantiate(particle[i]);
        //                particle[i].Play();
        //                break;
        //            }
        //        }

        //    case SELECTTYPE.Random:
        //        var random = 0;
        //        random = Random.Range(0, m_stageImage.Length);
        //        for (int i = 0; i < m_stageImage.Length; i++)
        //        {
        //            if (random == i)
        //            {
        //                m_background.GetComponent<Image>().sprite = m_stageImage[i];
        //                Instantiate(particle[i]);
        //                particle[i].Play();
        //                break;
        //            }
        //        }

        //    default:
        //        break;
        //}


    }
}
