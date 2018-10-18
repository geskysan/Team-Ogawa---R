using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StageNumberSeting : MonoBehaviour {

    public enum STAGE
    {
        stage_01,
        stage_02,
        stage_03,
        stage_04,
        stage_05,
        stage_06,
        stage_07,
    }

    [SerializeField]
    Sprite[] m_stageImage;
    [SerializeField]
    GameObject m_background;

    private void Start()
    {
        
    }
}
