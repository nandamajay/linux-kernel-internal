// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2022, Linaro Limited

#include <dt-bindings/sound/qcom,q6afe.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <sound/soc.h>
#include <sound/soc-dapm.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <linux/soundwire/sdw.h>
#include <sound/jack.h>
#include <linux/input-event-codes.h>
#include "qdsp6/q6afe.h"
#include "qdsp6/q6prm.h"
#include "common.h"
#include "sdw.h"

static struct snd_soc_dapm_widget qcs9100_dapm_widgets[] = {
	SND_SOC_DAPM_HP("Headphone Jack", NULL),
	SND_SOC_DAPM_MIC("Mic Jack", NULL),
	SND_SOC_DAPM_SPK("DP0 Jack", NULL),
	SND_SOC_DAPM_SPK("DP1 Jack", NULL),
	SND_SOC_DAPM_SPK("DP2 Jack", NULL),
	SND_SOC_DAPM_SPK("DP3 Jack", NULL),
	SND_SOC_DAPM_SPK("DP4 Jack", NULL),
	SND_SOC_DAPM_SPK("DP5 Jack", NULL),
	SND_SOC_DAPM_SPK("DP6 Jack", NULL),
	SND_SOC_DAPM_SPK("DP7 Jack", NULL),
};

static struct snd_soc_dapm_route qcs9100_dapm_routes[] = {
};

struct snd_soc_common {
	char *driver_name;
	const struct snd_soc_dapm_widget *dapm_widgets;
	int num_dapm_widgets;
	const struct snd_soc_dapm_route *dapm_routes;
	int num_dapm_routes;
	int mi2s_dai_fmt;
	int jack_dai_id;
	bool mi2s_mclk_enable;
};

static struct snd_soc_common qcs9100_priv_data = {
	.driver_name = "sa8775p",
	.dapm_widgets = qcs9100_dapm_widgets,
	.num_dapm_widgets = ARRAY_SIZE(qcs9100_dapm_widgets),
	.dapm_routes = qcs9100_dapm_routes,
	.num_dapm_routes = ARRAY_SIZE(qcs9100_dapm_routes),
	.mi2s_dai_fmt = SND_SOC_DAIFMT_BP_FP,
	.jack_dai_id = QUINARY_MI2S_RX,
	.mi2s_mclk_enable = true,
};

static struct snd_soc_common qcm6490_priv_data = {
    .driver_name = "qcm6490",
    .dapm_widgets = qcs9100_dapm_widgets,
    .num_dapm_widgets = ARRAY_SIZE(qcs9100_dapm_widgets),
    .dapm_routes = qcs9100_dapm_routes,
    .num_dapm_routes = ARRAY_SIZE(qcs9100_dapm_routes),
    .mi2s_dai_fmt = SND_SOC_DAIFMT_BP_FP,
    .jack_dai_id = TX_CODEC_DMA_TX_3,
    .mi2s_mclk_enable = true,
};

static struct snd_soc_common qcs6490_priv_data = {
    .driver_name = "qcs6490",
    .dapm_widgets = qcs9100_dapm_widgets,
    .num_dapm_widgets = ARRAY_SIZE(qcs9100_dapm_widgets),
    .dapm_routes = qcs9100_dapm_routes,
    .num_dapm_routes = ARRAY_SIZE(qcs9100_dapm_routes),
    .mi2s_dai_fmt = SND_SOC_DAIFMT_BP_FP,
    .jack_dai_id = QUINARY_MI2S_RX,
    .mi2s_mclk_enable = true,
};

static struct snd_soc_common qcs615_priv_data = {
    .driver_name = "qcs6490",
    .dapm_widgets = qcs9100_dapm_widgets,
    .num_dapm_widgets = ARRAY_SIZE(qcs9100_dapm_widgets),
    .dapm_routes = qcs9100_dapm_routes,
    .num_dapm_routes = ARRAY_SIZE(qcs9100_dapm_routes),
    .mi2s_dai_fmt = SND_SOC_DAIFMT_BP_FP,
    .jack_dai_id = QUINARY_MI2S_RX,
    .mi2s_mclk_enable = true,
};

static struct snd_soc_common qcs8275_priv_data = {
    .driver_name = "qcs8300",
    .dapm_widgets = qcs9100_dapm_widgets,
    .num_dapm_widgets = ARRAY_SIZE(qcs9100_dapm_widgets),
    .dapm_routes = qcs9100_dapm_routes,
    .num_dapm_routes = ARRAY_SIZE(qcs9100_dapm_routes),
    .mi2s_dai_fmt = SND_SOC_DAIFMT_BP_FP,
    .jack_dai_id = QUINARY_MI2S_RX,
    .mi2s_mclk_enable = true,
};

static struct snd_soc_common sc8280xp_priv_data = {
    .driver_name = "sc8280xp",
    .dapm_widgets = qcs9100_dapm_widgets,
    .num_dapm_widgets = ARRAY_SIZE(qcs9100_dapm_widgets),
    .dapm_routes = qcs9100_dapm_routes,
    .num_dapm_routes = ARRAY_SIZE(qcs9100_dapm_routes),
    .mi2s_dai_fmt = SND_SOC_DAIFMT_BP_FP,
    .jack_dai_id = TX_CODEC_DMA_TX_3,
    .mi2s_mclk_enable = true,
};

static struct snd_soc_common sm8450_priv_data = {
    .driver_name = "sm8450",
    .dapm_widgets = qcs9100_dapm_widgets,
    .num_dapm_widgets = ARRAY_SIZE(qcs9100_dapm_widgets),
    .dapm_routes = qcs9100_dapm_routes,
    .num_dapm_routes = ARRAY_SIZE(qcs9100_dapm_routes),
    .mi2s_dai_fmt = SND_SOC_DAIFMT_BP_FP,
    .jack_dai_id = TX_CODEC_DMA_TX_3,
    .mi2s_mclk_enable = true,
};

static struct snd_soc_common sm8550_priv_data = {
    .driver_name = "sm8550",
    .dapm_widgets = qcs9100_dapm_widgets,
    .num_dapm_widgets = ARRAY_SIZE(qcs9100_dapm_widgets),
    .dapm_routes = qcs9100_dapm_routes,
    .num_dapm_routes = ARRAY_SIZE(qcs9100_dapm_routes),
    .mi2s_dai_fmt = SND_SOC_DAIFMT_BP_FP,
    .jack_dai_id = TX_CODEC_DMA_TX_3,
    .mi2s_mclk_enable = true,
};

static struct snd_soc_common sm8650_priv_data = {
    .driver_name = "sm8650",
    .dapm_widgets = qcs9100_dapm_widgets,
    .num_dapm_widgets = ARRAY_SIZE(qcs9100_dapm_widgets),
    .dapm_routes = qcs9100_dapm_routes,
    .num_dapm_routes = ARRAY_SIZE(qcs9100_dapm_routes),
    .mi2s_dai_fmt = SND_SOC_DAIFMT_BP_FP,
    .jack_dai_id = TX_CODEC_DMA_TX_3,
    .mi2s_mclk_enable = true,
};

static struct snd_soc_common sm8750_priv_data = {
    .driver_name = "sm8750",
    .dapm_widgets = qcs9100_dapm_widgets,
    .num_dapm_widgets = ARRAY_SIZE(qcs9100_dapm_widgets),
    .dapm_routes = qcs9100_dapm_routes,
    .num_dapm_routes = ARRAY_SIZE(qcs9100_dapm_routes),
    .mi2s_dai_fmt = SND_SOC_DAIFMT_BP_FP,
    .jack_dai_id = TX_CODEC_DMA_TX_3,
    .mi2s_mclk_enable = true,
};

struct sc8280xp_snd_data {
	bool stream_prepared[AFE_PORT_MAX];
	struct snd_soc_card *card;
	struct sdw_stream_runtime *sruntime[AFE_PORT_MAX];
	struct snd_soc_jack jack;
	struct snd_soc_jack dp_jack[8];
	struct snd_soc_common *snd_soc_common_priv;
	bool jack_setup;
};

static int sc8280xp_snd_init(struct snd_soc_pcm_runtime *rtd)
{
	struct sc8280xp_snd_data *data = snd_soc_card_get_drvdata(rtd->card);
	struct snd_soc_dai *cpu_dai = snd_soc_rtd_to_cpu(rtd, 0);
	struct snd_soc_card *card = rtd->card;
	struct snd_soc_jack *dp_jack  = NULL;
	int dp_pcm_id = 0;

	switch (cpu_dai->id) {
	case PRIMARY_MI2S_RX...QUATERNARY_MI2S_TX:
	case QUINARY_MI2S_RX...QUINARY_MI2S_TX:
	    if (data->snd_soc_common_priv->mi2s_dai_fmt)
		    snd_soc_dai_set_fmt(cpu_dai, data->snd_soc_common_priv->mi2s_dai_fmt);
	    else
		    snd_soc_dai_set_fmt(cpu_dai, SND_SOC_DAIFMT_BP_FP);
		break;
	case WSA_CODEC_DMA_RX_0:
	case WSA_CODEC_DMA_RX_1:
		/*
		 * Set limit of -3 dB on Digital Volume and 0 dB on PA Volume
		 * to reduce the risk of speaker damage until we have active
		 * speaker protection in place.
		 */
		snd_soc_limit_volume(card, "WSA_RX0 Digital Volume", 81);
		snd_soc_limit_volume(card, "WSA_RX1 Digital Volume", 81);
		snd_soc_limit_volume(card, "SpkrLeft PA Volume", 17);
		snd_soc_limit_volume(card, "SpkrRight PA Volume", 17);
		break;
	case DISPLAY_PORT_RX_0:
		/* DISPLAY_PORT dai ids are not contiguous */
		dp_pcm_id = 0;
		dp_jack = &data->dp_jack[dp_pcm_id];
		break;
	case DISPLAY_PORT_RX_1 ... DISPLAY_PORT_RX_7:
		dp_pcm_id = cpu_dai->id - DISPLAY_PORT_RX_1 + 1;
		dp_jack = &data->dp_jack[dp_pcm_id];
		break;
	default:
		break;
	}

	if (dp_jack)
		return qcom_snd_dp_jack_setup(rtd, dp_jack, dp_pcm_id);

	if (data->snd_soc_common_priv->jack_dai_id)
		return qcom_snd_jack_setup(rtd, &data->jack, &data->jack_setup,
					   data->snd_soc_common_priv->jack_dai_id);

	return 0;
}

static void sc8280xp_snd_shutdown(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = snd_soc_substream_to_rtd(substream);
	struct snd_soc_dai *cpu_dai = snd_soc_rtd_to_cpu(rtd, 0);
	struct sc8280xp_snd_data *pdata = snd_soc_card_get_drvdata(rtd->card);
	struct sdw_stream_runtime *sruntime = pdata->sruntime[cpu_dai->id];

	pdata->sruntime[cpu_dai->id] = NULL;
	sdw_release_stream(sruntime);
}

static int sc8280xp_be_hw_params_fixup(struct snd_soc_pcm_runtime *rtd,
				     struct snd_pcm_hw_params *params)
{
	struct snd_soc_dai *cpu_dai = snd_soc_rtd_to_cpu(rtd, 0);
	struct snd_interval *rate = hw_param_interval(params,
					SNDRV_PCM_HW_PARAM_RATE);
	struct snd_interval *channels = hw_param_interval(params,
					SNDRV_PCM_HW_PARAM_CHANNELS);
	struct snd_mask *fmt = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);

	rate->min = rate->max = 48000;
	snd_mask_set_format(fmt, SNDRV_PCM_FORMAT_S16_LE);
	channels->min = 2;
	channels->max = 2;
	switch (cpu_dai->id) {
	case TX_CODEC_DMA_TX_0:
	case TX_CODEC_DMA_TX_1:
	case TX_CODEC_DMA_TX_2:
	case TX_CODEC_DMA_TX_3:
		channels->min = 1;
		break;
	default:
		break;
	}


	return 0;
}

static int sc8280xp_snd_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = snd_soc_substream_to_rtd(substream);
	struct snd_soc_dai *cpu_dai = snd_soc_rtd_to_cpu(rtd, 0);
	struct sc8280xp_snd_data *pdata = snd_soc_card_get_drvdata(rtd->card);
	int ret = 0;

	if (pdata->snd_soc_common_priv->mi2s_mclk_enable) {
		switch (cpu_dai->id) {
		case PRIMARY_MI2S_RX...PRIMARY_MI2S_TX:
			ret = snd_soc_dai_set_sysclk(cpu_dai, Q6PRM_LPASS_CLK_ID_MCLK_1, 12288000, SND_SOC_CLOCK_IN);
			break;
		case SECONDARY_MI2S_RX...SECONDARY_MI2S_TX:
			ret = snd_soc_dai_set_sysclk(cpu_dai, Q6PRM_LPASS_CLK_ID_MCLK_2, 12288000, SND_SOC_CLOCK_IN);
			break;
		case TERTIARY_MI2S_RX...TERTIARY_MI2S_TX:
			ret = snd_soc_dai_set_sysclk(cpu_dai, Q6PRM_LPASS_CLK_ID_MCLK_3, 12288000, SND_SOC_CLOCK_IN);
			break;
		case QUATERNARY_MI2S_RX...QUATERNARY_MI2S_TX:
			ret = snd_soc_dai_set_sysclk(cpu_dai, Q6PRM_LPASS_CLK_ID_MCLK_4, 12288000, SND_SOC_CLOCK_IN);
			break;
		case QUINARY_MI2S_RX...QUINARY_MI2S_TX:
			ret = snd_soc_dai_set_sysclk(cpu_dai, Q6PRM_LPASS_CLK_ID_MCLK_5, 12288000, SND_SOC_CLOCK_IN);
			break;
		default:
			break;
		}

		if (ret < 0)
			dev_err(rtd->dev, "snd_soc_dai_set_sysclk err = %d\n", ret);
	}

	return qcom_snd_sdw_hw_params(substream, params, &pdata->sruntime[cpu_dai->id]);
}

static int sc8280xp_snd_prepare(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = snd_soc_substream_to_rtd(substream);
	struct snd_soc_dai *cpu_dai = snd_soc_rtd_to_cpu(rtd, 0);
	struct sc8280xp_snd_data *data = snd_soc_card_get_drvdata(rtd->card);
	struct sdw_stream_runtime *sruntime = data->sruntime[cpu_dai->id];

	return qcom_snd_sdw_prepare(substream, sruntime,
				    &data->stream_prepared[cpu_dai->id]);
}

static int sc8280xp_snd_hw_free(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = snd_soc_substream_to_rtd(substream);
	struct sc8280xp_snd_data *data = snd_soc_card_get_drvdata(rtd->card);
	struct snd_soc_dai *cpu_dai = snd_soc_rtd_to_cpu(rtd, 0);
	struct sdw_stream_runtime *sruntime = data->sruntime[cpu_dai->id];

	return qcom_snd_sdw_hw_free(substream, sruntime,
				    &data->stream_prepared[cpu_dai->id]);
}

static const struct snd_soc_ops sc8280xp_be_ops = {
	.startup = qcom_snd_sdw_startup,
	.shutdown = sc8280xp_snd_shutdown,
	.hw_params = sc8280xp_snd_hw_params,
	.hw_free = sc8280xp_snd_hw_free,
	.prepare = sc8280xp_snd_prepare,
};

static void sc8280xp_add_be_ops(struct snd_soc_card *card)
{
	struct snd_soc_dai_link *link;
	int i;

	for_each_card_prelinks(card, i, link) {
		if (link->no_pcm == 1) {
			link->init = sc8280xp_snd_init;
			link->be_hw_params_fixup = sc8280xp_be_hw_params_fixup;
			link->ops = &sc8280xp_be_ops;
		}
	}
}

static int sc8280xp_platform_probe(struct platform_device *pdev)
{
	struct snd_soc_card *card;
	struct sc8280xp_snd_data *data;
	struct device *dev = &pdev->dev;
	int ret;

	card = devm_kzalloc(dev, sizeof(*card), GFP_KERNEL);
	if (!card)
		return -ENOMEM;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data) {
		return -ENOMEM;
	}

	data->snd_soc_common_priv = (struct snd_soc_common *)of_device_get_match_data(dev);
	if (!data->snd_soc_common_priv)
		return -ENOMEM;

	card->dev = dev;
	dev_set_drvdata(dev, card);
	snd_soc_card_set_drvdata(card, data);
	card->dapm_widgets = data->snd_soc_common_priv->dapm_widgets;
	card->num_dapm_widgets = data->snd_soc_common_priv->num_dapm_widgets;
	card->dapm_routes = data->snd_soc_common_priv->dapm_routes;
	card->num_dapm_routes = data->snd_soc_common_priv->num_dapm_routes;

	ret = qcom_snd_parse_of(card);
	if (ret)
		return ret;

	card->driver_name = data->snd_soc_common_priv->driver_name;
	sc8280xp_add_be_ops(card);
	return devm_snd_soc_register_card(dev, card);
}

static const struct of_device_id snd_sc8280xp_dt_match[] = {
	{.compatible = "qcom,qcm6490-idp-sndcard", .data=&qcm6490_priv_data},
	{.compatible = "qcom,qcs615-sndcard", .data=&qcs6490_priv_data},
	{.compatible = "qcom,qcs6490-rb3gen2-sndcard", .data=&qcs6490_priv_data},
	{.compatible = "qcom,qcs8275-sndcard", .data=&qcs8275_priv_data},
	{.compatible = "qcom,qcs9075-sndcard", .data=&qcs9100_priv_data},
	{.compatible = "qcom,qcs9100-sndcard", .data=&qcs9100_priv_data},
	{.compatible = "qcom,sc8280xp-sndcard", .data=&sc8280xp_priv_data},
	{.compatible = "qcom,sm8450-sndcard", .data=&sm8450_priv_data},
	{.compatible = "qcom,sm8550-sndcard", .data=&sm8550_priv_data},
	{.compatible = "qcom,sm8650-sndcard", .data=&sm8650_priv_data},
	{.compatible = "qcom,sm8750-sndcard", .data=&sm8750_priv_data},
	{}
};

MODULE_DEVICE_TABLE(of, snd_sc8280xp_dt_match);

static struct platform_driver snd_sc8280xp_driver = {
	.probe  = sc8280xp_platform_probe,
	.driver = {
		.name = "snd-sc8280xp",
		.of_match_table = snd_sc8280xp_dt_match,
	},
};
module_platform_driver(snd_sc8280xp_driver);
MODULE_AUTHOR("Srinivas Kandagatla <srinivas.kandagatla@linaro.org");
MODULE_DESCRIPTION("SC8280XP ASoC Machine Driver");
MODULE_LICENSE("GPL");
